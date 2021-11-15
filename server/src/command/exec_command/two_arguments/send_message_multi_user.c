/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_message_multi_user
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

void send_without_log_history(char **array, client_t *client,
client_t *list_client)
{
    time_t timestamp = time(NULL);

    dprintf(client->socket, "%d %s\n", 200, "Message send.");
    dprintf(list_client->socket, "From\n%s\n%ld\n%s\n", client->username,
    timestamp, array[2]);
    printf("[MY_TEAMS EPITECH] Client [%d] \033[32m[Response] %d %s\033[0m\n",
    client->id, 200, "Message Send");
    printf("message from %s to %s: %s\n", client->username,
    list_client->username, array[2]);
}