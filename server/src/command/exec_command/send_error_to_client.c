/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_error_to_client
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "struct_server.h"
#include "include.h"

void send_error_to_client(client_t *client, int code, char *msg)
{
    dprintf(client->socket, "%d %s\n", code, msg);
    printf("[MY_TEAMS EPITECH] Client [%d] \033[32m[Response] %d %s\033[0m\n",
    client->id, code, msg);
}