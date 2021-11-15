/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** tools
*/

#include "include_client.h"

int get_code(char *message)
{
    char str[4];

    str[0] = message[0];
    str[1] = message[1];
    str[2] = message[2];
    str[3] = '\0';
    return atoi(str);
}

char *get_message(char *my_read, int nb)
{
    char *message = malloc(sizeof(char) * (nb));
    int i = 0;

    if (!message)
        return NULL;
    for (int j = 4; j < nb; i++, j++)
        message[i] = my_read[j];
    message[i] = '\0';
    return message;
}

int analyse_code(my_client_t *client, int code, char *message)
{
    if (!message || code < 0)
        print_message("Error when reading message", 0);
    if (code >= 200 && code < 300)
        return command_is_accepted(client, code, message);
    if (code >= 300 && code < 500)
        return command_is_temporary_refused(code, message);
    if (code >= 500)
        return command_is_refused(code, message);
    return 0;
}