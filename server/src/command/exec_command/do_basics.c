/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** do_basics
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
} client_commands_basics[9] = {
    {"/help", 0, false},
    {"/login", 1, false},
    {"/logout", 0, false},
    {"/users", 0, true},
    {"/user" , 1, true},
    {"/send", 2, true},
    {"/messages", 1, true},
    {"/subscribe", 1, true},
    {"/unsubscribe" , 1, true},
};

void help_logout_users(client_t *client, int command, client_t *list_client)
{
    switch (command)
    {
        case 0:
            display_help(client);
            break;
        case 2:
            logout_client(client, list_client);
            break;
        case 3:
            display_users(client, list_client);
            break;
        default:
            send_error_to_client(client, 500, "Invalid number of arguments");
            break;
    }
}

void send_message(client_t *client, int size, char *command,
client_t *list_client)
{
    switch (size)
    {
    case 5:
        send_message_to_user(client, command, list_client);
        break;
    default:
        send_error_to_client(client, 500, "Invalid number of arguments");
        break;
    }
}

void login_user_message_subscrie_unsubscribe(client_t *client, int size,
char *command, client_t *list_client)
{
    switch (size) {
    case 1:
        connect_client(client, command, list_client);
        break;
    case 4:
        get_info_user(client, list_client, command);
        break;
    case 6:
        display_messages(client, command);
        break;
    case 7:
        subscribe(client, command);
        break;
    case 8:
        unsubscribe(client, command);
        break;
    default:
        send_error_to_client(client, 500, "Invalid number of arguments");
        break;
    }
}

void do_basics(client_t *client, char *command, int nb_command,
client_t *list_client)
{
    command = clean_str(command);
    if (client_commands_basics[nb_command].must_be_connected == true &&
    client->is_connected == false) {
        send_to_client(client, 403, "Please login first");
    } else
        redir_in_command(client, command, nb_command, list_client);
}
