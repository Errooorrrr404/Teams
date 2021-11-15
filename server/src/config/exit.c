/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** exit
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

void exit_client(client_t *client)
{
    if (client->have_username == true)
        free(client->username);
    if (client->have_password == 1)
        free(client->password);
    client->have_username = false;
    client->have_password = 0;
    client->is_connected = false;
    close(client->socket);
    client->socket = -1;
}

void free_client(client_t *client)
{
    free(client);
}

void free_server(my_server_t *server)
{
    free(server);
}

void free_system(my_server_t *server, client_t *client)
{
    free_server(server);
    free_client(client);
}