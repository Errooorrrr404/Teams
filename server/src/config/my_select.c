/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** my_select
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

int is_activity(my_server_t *server, client_t *client)
{
    if (FD_ISSET(server->socket_server, &server->read_fds)) {
        connection(server, client);
    }
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client[i].socket != -1 && FD_ISSET(client[i].socket,
        &server->write_fds))
            recup_commande(&client[i], client);
        if (client[i].socket != -1 && FD_ISSET(client[i].socket,
        &server->read_fds))
            recup_commande(&client[i], client);
        if (client[i].shutdown == 1)
            return 1;
    }
    return 0;
}

int select_client(int activity, my_server_t *server, client_t *client)
{
    if (activity > 0)
        return is_activity(server, client);
    return 0;
}