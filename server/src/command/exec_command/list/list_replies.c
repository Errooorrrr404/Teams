/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list_replies
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "struct_server.h"
#include "include.h"

void display_replies(client_t *client, char *str, struct stat s, int fd)
{
    int nb = read(fd, str, s.st_size);

    str[nb - 1] = '\0';
    dprintf(client->socket, "%d %s\nList of threads:\n%s", 200,
    "Command Okay.", str);
    printf("[MY_TEAMS EPITECH] Client [%d] ", client->id);
    printf("\033[32m[Response] %d %s\033[0m\n", 200, "Command Okay.");
}

void recup_replies(client_t *client, char *file, int fd)
{
    struct stat s;
    char *str;

    if (stat(file, &s) == -1) {
        send_error_to_client(client, 500, "Error when Listing Threads.");
        return;
    }
    str = malloc(sizeof(char) * (s.st_size + 1));
    if (!str) {
        send_error_to_client(client, 500, "Error when Listing Threads.");
        return;
    }
    display_replies(client, str, s, fd);
}

int check_folders(char *folder, client_t *client)
{
    if (!folder) {
        send_error_to_client(client, 500, "Error when Listing Threads.");
        return 84;
    }
    return 0;
}

void check_fd(client_t *client, int fd, char *folder)
{
    if (fd != -1) {
        recup_replies(client, folder, fd);
        close(fd);
    } else
        send_error_to_client(client, 500, "Invalid threads.");
}

void list_replies(client_t *client)
{
    int fd;
    char *folder = concat_path("./server/files/database/data/",
    client->use_team);

    if (check_folders(folder, client) == 84)
        return;
    folder = my_concat_path(folder, '/', client->use_channel);
    if (check_folders(folder, client) == 84)
        return;
    folder = my_concat_path(folder, '/', client->use_thread);
    if (check_folders(folder, client) == 84)
        return;
    folder = my_concat_path(folder, '/', "reply");
    if (check_folders(folder, client) == 84)
        return;
    fd = open(folder, O_RDONLY);
    check_fd(client, fd, folder);
    free(folder);
}