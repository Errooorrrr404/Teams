/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Ubuntu]
** File description:
** log_other_clients
*/

#include "include_client.h"

int display_user_disconnected(char *message)
{
    char **array = str_to_array(message, '\n');

    if (!array)
        return 84;
    client_event_loggedout(array[0], array[1]);
    free_array(array);
    return 0;
}