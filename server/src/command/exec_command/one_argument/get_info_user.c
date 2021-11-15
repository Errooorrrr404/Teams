/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** get_user
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

void display_info_user(client_t *client, client_t list_client)
{
    dprintf(client->socket, "%d %s\n\033[0m%s: %s\n%s: %d\n", 200,
    "Command Okay", "Username", list_client.username, "socket",
    list_client.socket);
    printf("[MY_TEAMS EPITECH] Client [%d] \033[32m[Response] %d %s\033[0m\n",
    client->id, 200, "Command Okay");
}

void analyse_info_user(char **array, char *name, client_t *client,
client_t *list_client)
{
    for (int i = 0; list_client[i].socket != -1; i++) {
        if (list_client[i].have_username == true &&
        strcmp(name, list_client[i].username) == 0
        && client->socket != list_client[i].socket) {
            display_info_user(client, list_client[i]);
            free_array(array);
            free(name);
            return;
        }
    }
    send_to_client(client, 500, "Invalid username");
    free_array(array);
    free(name);
}

void get_info_user(client_t *client, client_t *list_client, char *command)
{
    char **array = str_to_array(command, ' ');
    char *name;

    if (!array) {
        send_error_to_client(client, 500,
            "Error when loaded information about the client.");
        return;
    }
    name = str_without_quotes(array[1]);
    if (!name) {
        send_error_to_client(client, 500,
            "Error when loaded information about the client.");
        free_array(array);
        return;
    }
    analyse_info_user(array, name, client, list_client);
}