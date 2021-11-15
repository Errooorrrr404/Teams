/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create
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

void which_is_create(client_t *client, char **array)
{
    if (client->use_is_team == false && client->use_is_channel == false &&
    client->use_is_thread == false) {
        create_team(client, array);
        return;
    }
    if (client->use_is_team == true && client->use_is_channel == false &&
    client->use_is_thread == false) {
        create_channel(client, array);
        return;
    }
    if (client->use_is_team == true && client->use_is_channel == true &&
    client->use_is_thread == false) {
        create_thread(client, array);
        return;
    }
    send_error_to_client(client, 500, "Invalid /use.");
}

void switch_create(client_t *client, char **array, int size)
{
    switch (size) {
        case 2:
            if (client->use_is_team == true &&
            client->use_is_channel == true && client->use_is_thread == true)
                reply_to_thread(client, array);
            else
                send_to_client(client, 500,
                "Invalid number of arguments or /use isn't defined correctly.");
            break;
        case 3:
            which_is_create(client, array);
            break;
        default:
            send_to_client(client, 500, "Invalid number of arguments");
            break;
    }
}

void create_command(client_t *client, char *command)
{
    char **array = command_to_array(command, client);
    int size = size_array(array);

    if (!array)
        return;
    switch_create(client, array, size);
    free_and_unset_use(client);
    free_array(array);
}