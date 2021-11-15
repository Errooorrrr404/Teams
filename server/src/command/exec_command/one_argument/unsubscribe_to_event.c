/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** subscribe
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "struct_server.h"
#include "include.h"

void changes_subscribed(client_t *client, int is_in, char *str, char *path)
{
    int fd = open(path, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    int is_changed = 0;

    if (fd == -1) {
        send_error_to_client(client, 500, "Error with the file access.");
        return;
    }
    if (is_in == 0) {
        dprintf(fd, "%s", delete_account(client->username, str));
        is_changed = 1;
    }
    close(fd);
    if (is_changed == 1) {
        send_to_client(client, 200, "Unsubscribe Successful.");
        unsubscribe_log(client);
    } else
        send_to_client(client, 500,
        "You are not registered in this team.");
}

int my_check(client_t *client, char **array)
{
    for (int i = 0; array[i]; i++) {
        if (strcmp(array[i], client->username) == 0)
            return 0;
    }
    return 84;
}

void check_client_in_file(client_t *client, char *path, char *str)
{
    char **array = str_to_array(str, '\n');
    int check = 0;

    if (!array) {
        send_error_to_client(client, 500, "Error when unsubcrining team.");
        return;
    }
    check = my_check(client, array);
    free_array(array);
    if (check == -1) {
        send_error_to_client(client, 500, "Error when unsubscribe in team.");
    } else {
        changes_subscribed(client, check, str, path);
    }
}

void unsubscribe_in_team(client_t *client, char *path, struct stat s)
{
    int fd = open(path, O_RDONLY);
    char *str = malloc(sizeof(char) * (s.st_size + 1));
    int nb;

    if (!str || fd == -1) {
        send_error_to_client(client, 500, "The file doesn't exist.");
        return;
    }
    nb = read(fd, str, s.st_size);
    close(fd);
    if (nb > 0) {
        str[nb - 1] = '\0';
        check_client_in_file(client, path, str);
    } else
        send_error_to_client(client, 500,
        "You are not already registered in this team.");
    free(str);
}

int check_errors_unsubscribe(void *folder, client_t *client)
{
    if (!folder) {
        send_error_to_client(client, 500, "Error when creating channel.");
        return 84;
    }
    return 0;
}