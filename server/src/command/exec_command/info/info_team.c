/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** info_team
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

void display_info_team(client_t *client, struct stat s, int fd)
{
    int nb;
    char *str = malloc(sizeof(char) * (s.st_size + 1));

    if (!str) {
        close(fd);
        send_error_to_client(client, 500, "Error when loading info of team.");
        return;
    }
    nb = read(fd, str, s.st_size);
    str[nb - 1] = '\0';
    dprintf(client->socket, "%d %s\nInfo of the team\"%s\":\n%s", 200,
    "Command Okay.", client->use_team, str);
    printf("[MY_TEAMS EPITECH] Client [%d] ", client->id);
    printf("\033[32m[Response] %d %s\033[0m\n", 200, "Command Okay.");
}

void check_info_team(client_t *client, struct stat s, char *file)
{
    int fd = open(file, O_RDONLY);

    if (fd == -1) {
        send_error_to_client(client, 500, "The team is not available.");
        return;
    }
    display_info_team(client, s, fd);
}

void info_team(client_t *client)
{
    struct stat s;
    char *file = concat_path("./server/files/database/data/", client->use_team);

    if (!file) {
        send_error_to_client(client, 500, "Error when loading info of team.");
        return;
    }
    file = my_concat_path(file, '/', "description");
    if (!file) {
        send_error_to_client(client, 500, "Error when loading info of team.");
        return;
    }
    if (stat(file, &s)  == -1) {
        send_error_to_client(client, 500, "Error when loading info of team.");
        return;
    }
    check_info_team(client, s, file);
}