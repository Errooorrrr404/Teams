/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** unset_use
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

void free_and_unset_use(client_t *client)
{
    if (client->use_is_team == true)
        free(client->use_team);
    if (client->use_is_channel == true)
        free(client->use_channel);
    if (client->use_is_thread == true)
        free(client->use_thread);
    client->use_defined = false;
    client->use_is_team = false;
    client->use_is_channel = false;
    client->use_is_thread = false;
}

void unset_use(client_t *client)
{
    if (client->use_defined == false) {
        send_to_client(client, 200, "Command Okay");
    } else
        free_and_unset_use(client);
}