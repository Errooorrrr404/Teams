/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** loop
*/

#include <sys/signal.h>
#include "include_client.h"

int build_fd_sets(my_client_t *client)
{
    FD_ZERO(&client->read_fds);
    FD_SET(STDIN_FILENO, &client->read_fds);
    FD_SET(client->socket_server, &client->read_fds);
    FD_ZERO(&client->write_fds);
    FD_ZERO(&client->except_fds);
    FD_SET(STDIN_FILENO, &client->except_fds);
    FD_SET(client->socket_server, &client->except_fds);
    return 0;
}

int read_from_server(my_client_t *client)
{
    int nb = 0;

    nb = listen_read_server(client, nb);
    nb = listen_write_server(client, nb);
    return nb;
}

int is_activity(my_client_t *client)
{
    int nb = 0;
    char *input;
    size_t len = 0;

    if (FD_ISSET(STDIN_FILENO, &client->read_fds)) {
        input = NULL;
        nb = getline(&input, &len, stdin);
        if (nb == -1) {
            free(input);
            return 1;
        }
        input[nb] = '\0';
        if (nb > 1 && strncmp(input, "exit", strlen(input) - 1) == 0) {
            free(input);
            return 1;
        }
        dprintf(client->socket_server, "%s", input);
        free(input);
    }
    return read_from_server(client);
}

void loop(my_client_t *client, int nb)
{
    int maxfd = client->socket_server;
    int activity;

    while (1) {
        build_fd_sets(client);
        activity = select(maxfd + 1, &client->read_fds, &client->write_fds,
        &client->except_fds, NULL);
        if (activity > 0) {
            nb = is_activity(client);
            if (nb == 1)
                break;
        }
    }
}