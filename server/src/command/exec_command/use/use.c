/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** use
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

void switch_size(client_t *client, char **array, int size)
{
    switch (size) {
        case 1:
            unset_use(client);
            break;
        case 2:
            set_team(client, array);
            break;
        case 3:
            set_team_channel(client, array);
            break;
        case 4:
            set_team_channel_thread(client, array);
            break;
        default:
            send_to_client(client, 500, "Invalid number of arguments");
            break;
    }
}

void use_command(client_t *client, char *command)
{
    char **array = command_to_array(command, client);
    int size = size_array(array);

    if (!array)
        return;
    switch_size(client, array, size);
    free_array(array);
}