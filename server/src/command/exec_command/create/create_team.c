/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_team
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

int write_in_file(client_t *client, char *path, char *name_team, char *message)
{
    int fd = open(path, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    char *str;
    if (fd == -1)
        return -1;
    if (message[strlen(message) - 1] == ' ')
        message[strlen(message) - 1] = '\0';
    dprintf(fd, "%s\n", message);
    str = set_uuid_client(fd);
    if (str && client->have_uuid == true && client->use_is_team == false) {
        server_event_team_created(str, name_team, client->uuid);
        dprintf(client->socket, "202\n%s\n%s\n%s", str, name_team,
        message);
    }
    free(str);
    close(fd);
    return 0;
}

int create_acces_file(char *path_folder)
{
    char *file = concat_path(path_folder, "/access.config");
    int fd;

    if (!file)
        return -1;
    fd = open(file, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    free(file);
    if (fd == -1)
        return -1;
    close(fd);
    return 0;
}

void add_team(client_t *client, char **array, char *folder)
{
    char *description = concat_path(folder, "/description");

    if (!description) {
        send_error_to_client(client, 500, "Error when creating team.");
        return;
    }
    if (write_in_file(client, description, array[1], array[2]) == -1) {
        free(description);
        send_error_to_client(client, 500, "Error when creating team.");
        return;
    }
    if (create_acces_file(folder) == -1) {
        free(description);
        send_error_to_client(client, 500, "Error when creating team.");
        return;
    }
    free(description);
}

void create_team(client_t *client, char **array)
{
    int fd;
    struct stat s;
    char *folder = concat_path("./server/files/database/data/", array[1]);

    if (!folder) {
        send_error_to_client(client, 500, "Error when creating team.");
        return;
    }
    if (stat(folder, &s) != -1) {
        send_error_to_client(client, 520, "The team already exists.");
    } else {
        fd = mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (fd == -1) {
            send_error_to_client(client, 500, "Error when creating team.");
        } else
            add_team(client, array, folder);
    }
    free(folder);
}