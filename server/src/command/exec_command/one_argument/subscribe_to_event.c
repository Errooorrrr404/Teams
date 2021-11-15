/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** subscribe
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "struct_server.h"
#include "include.h"

void added_client_in_file(client_t *client, char *path, char *desc)
{
    int fd = open(path, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    char *uuid;

    if (fd == -1) {
        send_error_to_client(client, 500, "The file doesn't exist.");
        return;
    }
    dprintf(fd, "%s\n", client->username);
    close(fd);
    uuid = get_last_line(desc);
    if (!uuid) {
        send_to_client(client, 500, "Error when subscribe in team");
        return;
    }
    send_to_client(client, 200, "Registration Successful.");
    server_event_user_join_a_team(uuid, client->uuid);
    free(uuid);
}

void subscribe_in_team(client_t *client, char *path, char *desc, struct stat s)
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
        if (strstr(str, client->username)) {
            send_error_to_client(client, 500,
            "You are already registered in this team.");
        } else
            added_client_in_file(client, path, desc);
    } else
        added_client_in_file(client, path, desc);
    free(str);
}

int check_errors_subscribe(void *folder, client_t *client)
{
    if (!folder) {
        send_error_to_client(client, 500, "Error when creating channel.");
        return 84;
    }
    return 0;
}

void setup_subscribe(client_t *client)
{
    char *folder = concat_path("./server/files/database/data/",
    client->use_team);
    struct stat s;
    char *description;

    if (check_errors_subscribe(folder, client) == 84)
        return;
    description = strdup(folder);
    if (check_errors_subscribe(description, client) == 84)
        return;
    folder = my_concat_path(folder, '/', "access.config");
    if (check_errors_subscribe(folder, client) == 84)
        return;
    description = my_concat_path(description, '/', "description");
    if (check_errors_subscribe(description, client) == 84)
        return;
    stat(folder, &s);
    subscribe_in_team(client, folder, description, s);
    free(folder);
    free(description);
}

void subscribe(client_t *client, char *command)
{
    char **array = command_to_array(command, client);
    int nb = 0;

    free_and_unset_use(client);
    if (!array) {
        send_to_client(client, 500, "Error when searching in database.");
        return;
    }
    if (array[1][strlen(array[1]) - 1] != '\0')
        array[1][strlen(array[1]) - 1] = '\0';
    nb = search_team_in_database(client, array[1]);
    free_array(array);
    if (nb == -1)
        send_to_client(client, 500, "Error when searching in database.");
    else if (nb == 0)
        setup_subscribe(client);
    else
        send_to_client(client, 500, "The team doesn't exist.");
    free_and_unset_use(client);
}
