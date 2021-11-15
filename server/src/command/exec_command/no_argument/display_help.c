/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** display_help
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

void send_help(client_t *client, char *str, struct stat s, int fd)
{
    int nb = read(fd, str, s.st_size);

    str[nb - 1] = '\0';
    dprintf(client->socket, "200 Command Okay\033[0m\n%s\n", str);
    printf("[MY_TEAMS EPITECH] Client [%d] \033[32m[Response] %d %s\033[0m\n",
    client->id, 200, "Command Okay");
}

void display_help(client_t *client)
{
    struct stat s;
    char *str;
    int fd;

    if (stat("server/files/help.txt", &s)  == -1)
        return;
    fd = open("server/files/help.txt", O_RDONLY);
    if (fd == -1)
        return;
    str = malloc(sizeof(char) * (s.st_size + 1));
    if (!str) {
        close(fd);
        return;
    }
    send_help(client, str, s, fd);
}