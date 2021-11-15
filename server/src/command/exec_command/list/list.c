/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list
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

void which_is_list(client_t *client)
{
    if (client->use_is_team == false && client->use_is_channel == false &&
    client->use_is_thread == false) {
        list_teams(client);
        return;
    } else if (client->use_is_team == true && client->use_is_channel == false &&
    client->use_is_thread == false) {
        list_channels(client);
        return;
    }
    if (client->use_is_team == true && client->use_is_channel == true &&
    client->use_is_thread == false) {
        list_threads(client);
        return;
    } else if (client->use_is_team == true && client->use_is_channel == true &&
    client->use_is_thread == true) {
        list_replies(client);
        return;
    }
    send_error_to_client(client, 500, "Invalid /use.");
}

void switch_list(client_t *client, int size)
{
    switch (size) {
        case 1:
            which_is_list(client);
            break;
        default:
            send_to_client(client, 500, "Invalid number of arguments");
            break;
    }
}

void list_command(client_t *client, char *command)
{
    char **array = command_to_array(command, client);
    int size = size_array(array);

    if (!array)
        return;
    switch_list(client, size);
    free_and_unset_use(client);
    free_array(array);
}