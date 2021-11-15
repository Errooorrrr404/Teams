/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** free_array
*/

#include "include_client.h"

void free_array(char **array)
{
    for (size_t i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}