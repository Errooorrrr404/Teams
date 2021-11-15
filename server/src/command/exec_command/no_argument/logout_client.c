/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** logout_client
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

void free_defined(client_t *client)
{
    if (client->use_is_team == true)
        free(client->use_team);
    if (client->use_is_channel == true)
        free(client->use_channel);
    if (client->use_is_thread == true)
        free(client->use_thread);
    if (client->have_uuid == true)
        free(client->uuid);
    client->use_defined = false;
    client->use_is_team = false;
    client->use_is_channel = false;
    client->use_is_thread = false;
    client->have_uuid = false;
}

void send_data_to_other_clients(client_t *client, client_t *list_client)
{
    if (client->have_username == false || client->have_username == false)
        return;
    for (int i = 0; i != MAX_CLIENTS; i++) {
        if (list_client[i].is_connected == true &&
        list_client[i].socket != client->socket)
            dprintf(list_client[i].socket, "401\n%s\n%s", client->uuid,
            client->username);
    }
}

void logout_client(client_t *client, client_t *list_clients)
{
    send_to_client(client, 221, "Good Bye!");
    if (client->have_uuid == true)
        server_event_user_logged_out(client->uuid);
    if (client->socket != -1) {
        close(client->socket);
        client->socket = -1;
    }
    send_data_to_other_clients(client, list_clients);
    if (client->have_username == true)
        free(client->username);
    client->username = 0;
    client->is_connected = false;
    client->have_message_to_free = 0;
    for (int i = 0; i < MAX_CLIENTS; i++)
        free(client->message_array[i]);
    free(client->message_array);
    free_defined(client);
}