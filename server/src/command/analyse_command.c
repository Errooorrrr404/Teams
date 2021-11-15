/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** analyse_command
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

static struct {
    char *command;
    int nb_argument_required;
    bool must_be_connected;
} client_commands_basics[13] = {
    {"/help", 0, false},
    {"/login", 1, false},
    {"/logout", 0, false},
    {"/users", 0, true},
    {"/user" , 1, true},
    {"/send", 2, true},
    {"/messages", 1, true},
    {"/subscribe", 1, true},
    {"/unsubscribe" , 1, true},
    {"/create" , -1, true},
    {"/list" , -1, true},
    {"/info" , -1, true},
    {"/use" , -1, true},
};

int check_client_commands_basics(char *command)
{
    for (int i = 0; i < 13; i++) {
        if (strstr(command, client_commands_basics[i].command))
            return i;
    }
    if (strstr(command, "shutdown_server_now"))
        return -2;
    return -1;
}

void check_which_command(client_t *client, char *command,
client_t *list_client, int nb_command)
{
    switch (nb_command) {
        case 0:
            create_command(client, command);
            break;
        case 1:
            list_command(client, command);
            break;
        case 2:
            info_command(client, command, list_client);
            break;
        case 3:
            use_command(client, command);
            break;
    }
}

void check_is_create_info_list_use(client_t *client, char *command,
client_t *list_client)
{
    char **array = str_to_array(command, ' ');
    char *command_array[4] = {"/create", "/list", "/info", "/use"};
    int i = 0;

    if (!array) {
        send_error_to_client(client, 500, "Error when loaded informations.");
        return;
    }
    for (; i < 4; i++) {
        if (strstr(array[0], command_array[i])) {
            check_which_command(client, command, list_client, i);
            break;
        }
    }
    if (i == 4)
        send_error_to_client(client, 500, "Invalid Command.");
    free_array(array);
}

void analyse_command_client(client_t *client, char *command,
client_t *list_client)
{
    int nb = 0;

    nb = check_client_commands_basics(command);
    if (nb == -2) {
        client->shutdown = 1;
        return;
    }
    if (nb == -1)
        send_error_to_client(client, 500, "Invalid Command.");
    else if (nb > 0 && nb < 9)
        do_basics(client, command, nb, list_client);
    else {
        if (client->is_connected == false)
            send_error_to_client(client, 403, "Please login first");
        else
            check_is_create_info_list_use(client, command, list_client);
    }
}