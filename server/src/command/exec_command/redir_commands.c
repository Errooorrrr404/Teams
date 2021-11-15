/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** redir_commands
*/

#include "struct_server.h"
#include "include.h"

int check_error_command(char **array, int nb, client_t *client)
{
    if (!array || nb < 0) {
        send_error_to_client(client, 500, "Error \" missing");
        return 84;
    }
    return 0;
}

void redir_in_command(client_t *client, char *command, int nb_command,
client_t *list_client)
{
    char **array = command_to_array(command, client);
    int nb = size_array(array);

    if (!array)
        return;
    switch (nb) {
        case 1:
            help_logout_users(client, nb_command, list_client);
            break;
        case 2:
            login_user_message_subscrie_unsubscribe(client, nb_command,
            command, list_client);
            break;
        case 3:
            send_message(client, nb_command, command, list_client);
            break;
        default:
            send_error_to_client(client, 500, "Invalid number of arguments");
    }
    free_array(array);
}