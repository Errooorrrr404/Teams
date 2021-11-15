/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** unsubscribe
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include "include.h"

int is_good_word(char *str, char *login, int pos)
{
    size_t i = 0;

    for (; i < strlen(login); i++, pos++) {
        if (str[pos] != login[i])
            return -1;
    }
    return 1;
}

char *delete_login(char *str, char *login, int pos)
{
    for (size_t i = 0; i < strlen(login); i++, pos++) {
        str[pos] = '-';
    }
    return str;
}

char *delete_account(char *login, char *str)
{
    int check = 0;

    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == login[0])
            check = is_good_word(str, login, i);
        if (check == 1) {
            str = delete_login(str, login, i);
            break;
        }
    }
    return str;
}

void setup_unsubscribe(client_t *client)
{
    struct stat s;
    char *folder;

    folder = concat_path("./server/files/database/data/", client->use_team);
    if (!folder) {
        send_to_client(client, 500, "Error when unsubscribe in team.");
        return;
    }
    folder = my_concat_path(folder, '/', "access.config");
    if (!folder) {
        send_to_client(client, 500, "Error when unsubscribe in team.");
        return;
    }
    if (stat(folder, &s) == -1)
        send_error_to_client(client, 500, "The team doesn't exist.");
    else
        unsubscribe_in_team(client, folder, s);
    free(folder);
}

void unsubscribe(client_t *client, char *command)
{
    char **array = command_to_array(command, client);
    int nb = 0;

    free_and_unset_use(client);
    if (check_errors_unsubscribe(array, client) == 84)
        return;
    if (array[1][strlen(array[1]) - 1] != '\0')
        array[1][strlen(array[1]) - 1] = '\0';
    nb = search_team_in_database(client, array[1]);
    if (nb == 0)
        setup_unsubscribe(client);
    else if (nb == 1)
        send_to_client(client, 500, "Error when unsubscribe in team.");
    else
        send_to_client(client, 500, "The team doesn't exist.");
    free_and_unset_use(client);
    free_array(array);
}
