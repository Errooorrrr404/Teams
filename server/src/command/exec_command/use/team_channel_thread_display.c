/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** team_channel_thread_display
*/

#include "struct_server.h"
#include "include.h"

void check_display_team_channel(int my_error, client_t *client)
{
    if (my_error == -1)
        send_to_client(client, 500, "Error when searching in database.");
    else if (my_error == 0)
        send_to_client(client, 200, "Command Okay.");
    else {
        send_to_client(client, 500, "The channel doesn't exist.");
        free_and_unset_use(client);
    }
}

void check_display_team_channel_thread(client_t *client,
char **array, int my_error)
{
    if (my_error == -1)
        send_to_client(client, 500, "Error when searching in database.");
    else if (my_error == 0) {
        my_error = search_thread_in_database(client, array[3]);
        if (my_error == -1)
            send_to_client(client, 500, "Error when searching in database.");
        else if (my_error == 0)
            send_to_client(client, 200, "Command Okay.");
        else {
            send_to_client(client, 500, "The Thread doesn't exist.");
            free_and_unset_use(client);
        }
    } else {
        send_to_client(client, 500, "The channel doesn't exist.");
        free_and_unset_use(client);
    }
}