/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** display_users
*/

#include "include_client.h"

int size_array(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return i;
}

int print_users(char *message, int my_return)
{
    char **array = str_to_array(message, '\n');

    printf("%s\n", array[0]);
    for (int i = 1; i + 1 < size_array(array) - 2 ; i += 3) {
        client_print_users(array[i], array[i + 1], atoi (array[i + 2]));
    }
    free_array(array);
    return my_return;
}

int print_list(char *message, int my_return, int code)
{
    char **array = str_to_array(message, '\n');

    for (int i = 2; i + 1 < size_array(array); i += 3) {
        switch (code) {
            case 205:
                client_print_teams(array[i + 1], array[i], array[i + 2]);
                break;
            case 206:
                client_team_print_channels(array[i + 1],
                array[i], array[i + 2]);
                break;
        }
    }
    free_array(array);
    return my_return;
}

int display_list_message(char *message, int my_return)
{
    char **array = str_to_array(message, '\n');

    if (!array)
        return my_return;
    for (int i = 0; i < size_array(array); i += 4) {
        if (array[i + 2][strlen(array[i + 2])] != '\0')
            array[i + 2][strlen(array[i + 2])] = '\0';
        client_private_message_print_messages(array[i + 1], atoi(array[i + 2]),
        array[i + 3]);
    }
    free_array(array);
    return my_return;
}