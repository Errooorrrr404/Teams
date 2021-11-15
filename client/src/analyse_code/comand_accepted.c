/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** comand_accepted
*/

#include "include_client.h"

int print_channel_created(char *message)
{
    char **array = str_to_array(message, '\n');

    if (!array)
        return 0;
    client_print_channel_created(array[0], array[1], array[2]);
    free_array(array);
    return 0;
}

int print_team_created(char *message)
{
    char **array = str_to_array(message, '\n');

    if (!array)
        return 0;
    client_print_team_created(array[0], array[1], array[2]);
    free_array(array);
    return 0;
}

int print_thread_created(char *message)
{
    char **array = str_to_array(message, '\n');

    if (!array)
        return 0;
    client_print_thread_created(array[0], array[1], atoi(array[2]), array[3],
    array[4]);
    free_array(array);
    return 0;
}

int accepted_and_data_transfert(my_client_t *client, char *message, int code)
{
    if (code == 201)
        return print_channel_created(message);
    if (code == 201)
        return print_thread_created(message);
    if (code == 202)
        return print_team_created(message);
    if (code == 221) {
        if (client->have_uuid == true && client->have_uuid == true)
            client_event_loggedout(client->uuid, client->username);
        return print_message("Good Bye!", 1);
    }
    if (code == 230) {
        setup_data_client(client, message);
        if (client->have_username == true && client->have_uuid == true)
            client_event_loggedin(client->uuid, client->username);
        else
            return print_message("Error, please logout and login again!", 0);
        return 0;
    }
    return 0;
}

int display_new_user_connected(char *message)
{
    char **array = str_to_array(message, '\n');

    if (!array)
        return 84;
    client_event_loggedin(array[0], array[1]);
    free_array(array);
    return 0;
}