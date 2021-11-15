/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** code
*/

#include "include_client.h"

int print_message(char *message, int my_return)
{
    printf("From server: %s\n", message);
    return my_return;
}

void setup_data_client(my_client_t *client, char *message)
{
    char **array = str_to_array(message, '\n');

    if (!array)
        return;
    client->username = strdup(array[1]);
    if (!client->username) {
        printf("Error When Loading username");
    } else
        client->have_username = true;
    client->uuid = strdup(array[2]);
    if (!client->uuid) {
        printf("Error When Loading uuid");
    } else
        client->have_uuid = true;
    free_array(array);
}

int command_is_accepted(my_client_t *client, int code, char *message)
{
    if (code == 200)
        return print_message(message, 0);
    if (code == 204)
        return display_list_message(message, 0);
    if (code == 205 || code == 206)
        return print_list(message, 0, code);
    if (code == 210)
        return print_users(message, 0);
    if (code == 220)
        return print_message(message, 0);
    return accepted_and_data_transfert(client, message, code);
}

int command_is_temporary_refused(int code, char *message)
{
    if (code == 400)
        return display_new_user_connected(message);
    if (code == 401)
        return display_user_disconnected(message);
    if (code == 404)
        return print_message(
        "Ressource is temporarily unavailable. Please try again later.", 0);
    if (code == 403) {
        if (strstr(message, "first")) {
            client_error_unauthorized();
            return 0;
        }
        return 0;
    }
    return 0;
}

int command_is_refused(int code, char *message)
{
    if (code == 500)
        return print_message(message, 0);
    if (code == 520) {
        client_error_already_exist();
        return 0;
    }
    if (code == 530) {
        return print_message(message, 0);
    }
    return 0;
}