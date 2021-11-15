/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** my_server
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

void core_server(client_t *client, my_server_t *server, int activity,
int high_sock)
{
    signal(SIGINT, sigint_handler);
    while (1) {
        activity = 0;
        build_fd_sets(server, client);
        high_sock = server->socket_server;
        for (int i = 0; i < MAX_CLIENTS; i++)
            if (client[i].socket > high_sock)
                high_sock = client[i].socket;
        activity = select(high_sock + 1, &server->read_fds, &server->write_fds,
        &server->except_fds, NULL);
        if (select_client(activity, server, client) == 1)
            break;
    }
}

int loop_server(my_server_t *server, client_t *client)
{
    int high_sock = server->socket_server;
    int activity = 0;
    int flags = fcntl(0, F_GETFL, 0);

    if (loaded_client() == -1)
        return 84;
    fcntl(0, F_SETFL, flags | O_NONBLOCK);
    printf("\n");
    my_message_server("Waiting for connections...", 0);
    core_server(client, server, activity, high_sock);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client[i].socket != -1) {
            logout_client(&client[i], &client[i]);
        }
    }
    return 0;
}

int my_server(char *port)
{
    int my_ret = 0;
    my_server_t *server = malloc(sizeof(my_server_t));
    client_t *client;

    my_message_server("Starting Server...", 0);
    if (!server)
        return 84;
    if (init_server(port, server, 1) != 0) {
        free(server);
        return 84;
    }
    client = malloc(sizeof(client_t) * (MAX_CLIENTS + 1));
    if (init_client(client) != 0) {
        free(server);
        return 84;
    }
    printf("[MY_TEAMS EPITECH] Listener on Port: %d\n\n", server->port);
    my_ret = loop_server(server, client);
    free_system(server, client);
    return my_message_server("Stopping Server...", my_ret);
}