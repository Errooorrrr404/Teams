/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** info
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

void which_is_info(client_t *client, client_t *list_client)
{
    if (client->use_is_team == false && client->use_is_channel == false &&
    client->use_is_thread == false) {
        display_users(client, list_client);
        return;
    } else if (client->use_is_team == true && client->use_is_channel == false &&
    client->use_is_thread == false) {
        info_team(client);
        return;
    }
    if (client->use_is_team == true && client->use_is_channel == true &&
    client->use_is_thread == false) {
        info_channel(client);
        return;
    } else if (client->use_is_team == true && client->use_is_channel == true &&
    client->use_is_thread == true) {
        info_thread(client);
        return;
    }
    send_error_to_client(client, 500, "Invalid /info.");
}

void switch_info(client_t *client, int size, client_t *list_client)
{
    switch (size) {
        case 1:
            which_is_info(client, list_client);
            break;
        default:
            send_to_client(client, 500, "Invalid number of arguments");
            break;
    }
}

void info_command(client_t *client, char *command, client_t *list_client)
{
    char **array = command_to_array(command, client);
    int size = size_array(array);

    if (!array)
        return;
    switch_info(client, size, list_client);
    free_and_unset_use(client);
    free_array(array);
}