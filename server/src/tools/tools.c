/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** tools
*/

#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "include.h"
#include "struct_server.h"

int size_array(char **array)
{
    int i = 0;

    if (!array)
        return 0;
    for (; array[i]; i++);
    return i;
}

char *recup_str(char *msg, char *type)
{
    char *str = malloc(sizeof(char) * (strlen(msg) - strlen(type) + 1));
    int i = 0;

    if (!str)
        return NULL;
    for (size_t j = strlen(type) + 1; j < strlen(msg); j++, i++)
        str[i] = msg[j];
    str[i] = '\0';
    return str;
}

void send_to_client(client_t *client, int code, char *msg)
{
    if (client->socket > 0) {
        dprintf(client->socket, "%d %s\n", code, msg);
        printf("[MY_TEAMS EPITECH] Client [%d] ", client->id);
        printf("\033[32m[Response] %d %s\033[0m\n", code, msg);
    }
}

void sigint_handler( __attribute__((unused)) int sig_num)
{
    signal(SIGINT, sigint_handler);
    write(1, "\n", strlen("\n"));
}

int my_message_server(char *message, int return_value)
{
    printf("[MY_TEAMS EPITECH] %s\n", message);
    return return_value;
}
