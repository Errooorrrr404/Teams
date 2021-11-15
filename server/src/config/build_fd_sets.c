/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** build_fd_sets
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

int build_fd_sets(my_server_t *server, client_t *client)
{
    FD_ZERO(&server->read_fds);
    FD_SET(STDIN_FILENO, &server->read_fds);
    FD_SET(server->socket_server, &server->read_fds);
    for (int i = 0; i < MAX_CLIENTS; i++)
        if (client[i].socket != -1)
            FD_SET(client[i].socket, &server->read_fds);
    FD_ZERO(&server->write_fds);
    FD_ZERO(&server->except_fds);
    FD_SET(STDIN_FILENO, &server->except_fds);
    FD_SET(server->socket_server, &server->except_fds);
    for (int i = 0; i < MAX_CLIENTS; i++)
        if (client[i].socket != -1)
            FD_SET(client[i].socket, &server->except_fds);
    return 0;
}