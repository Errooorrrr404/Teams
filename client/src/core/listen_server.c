/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** listen_server
*/

#include "include_client.h"

void display_message_from_client(char *message)
{
    char **array = str_to_array(message, '\n');

    if (!array)
        return;
    client_event_private_message_received(array[1], array[3]);
    free_array(array);
}

int listen_write_server(my_client_t *client, int nb)
{
    char *message = NULL;
    char my_read[2048];

    if (FD_ISSET(client->socket_server, &client->write_fds)) {
        nb = recv(client->socket_server, my_read, 2047, 0);
        my_read[nb] = '\0';
        if (strstr(my_read, "From") && get_code(my_read) != 204)
            display_message_from_client(my_read);
        else {
            message = get_message(my_read, nb);
            nb = analyse_code(client, get_code(my_read), message);
        }
    }
    if (message != NULL)
        free (message);
    return nb;
}

int listen_read_server(my_client_t *client, int nb)
{
    char *message = NULL;
    char my_read[2048];

    if (FD_ISSET(client->socket_server, &client->read_fds)) {
        nb = recv(client->socket_server, my_read, 2047, 0);
        my_read[nb] = '\0';
        if (strstr(my_read, "From") && get_code(my_read) != 204)
            display_message_from_client(my_read);
        else {
            message = get_message(my_read, nb);
            nb = analyse_code(client, get_code(my_read), message);
        }
    }
    if (message != NULL)
        free (message);
    return nb;
}