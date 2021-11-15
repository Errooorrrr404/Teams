/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** command
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "struct_server.h"
#include "include.h"
#include "logging_server.h"

void analyse_command(client_t *client, char *command, client_t *list_client)
{
    analyse_command_client(client, command, list_client);
}

int analyse_valread(int valread, client_t *client, char *msg,
client_t *list_client)
{
    char user_id[10];

    sprintf(user_id, "%d", client->id);
    if (valread < 0)
        return 0;
    if (valread == 0 || strstr(msg, "logout")) {
        printf("[MY_TEAMS EPITECH] \033[31mClient disconnected, ip %s",
        inet_ntoa(client->address.sin_addr));
        printf(", port %d\033[0m\n", ntohs(client->address.sin_port));
        logout_client(client, list_client);
        return -1;
    }
    return 1;
}

int recup_commande(client_t *client, client_t *list_client)
{
    char *line;
    char msg[250];
    char *cmd;
    int valread;

    bzero(msg, 250);
    valread = read(client->socket, msg, 249);
    if (analyse_valread(valread, client, msg, list_client) != 1)
        return 0;
    if (!(line = strtok(msg, "\r\n")))
        return 0;
    cmd = strdup(msg);
    if (!cmd)
        return 0;
    printf("[MY_TEAMS EPITECH] Client [%d]\x1b[34m [Command] %s\x1b[0m\n",
    client->id, cmd);
    analyse_command(client, cmd, list_client);
    free(cmd);
    return 0;
}