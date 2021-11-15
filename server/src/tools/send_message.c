/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_message
*/
#include <string.h>
#include <stdio.h>
#include "include.h"

char *my_concat(char *src, char *dest)
{
    char *tmp = malloc(sizeof(char) * (strlen(src) + strlen(dest) + 3));
    int i = 0;

    if (!tmp) {
        free(src);
        return NULL;
    }
    for (size_t j = 0; j < strlen(src); j++, i++)
        tmp[i] = src[j];
    tmp[i] = '\n';
    i++;
    for (size_t j = 0; j < strlen(dest); j++, i++)
        tmp[i] = dest[j];
    tmp[i] = '\0';
    free(src);
    return tmp;
}

void send_message_to_client_with_argument(client_t *client, int code,
char *msg, char *str)
{
    dprintf(client->socket, "\033[0m%d %s\n%s\n", code, msg, str);
    printf("[MY_TEAMS EPITECH] Client [%d] \033[32m[Response] %d %s\033[0m\n",
    client->id, code, msg);
}