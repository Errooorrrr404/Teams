/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** str_without_quotes
*/

#include <string.h>
#include "include.h"

char *str_without_quotes(char *str)
{
    char *dest = malloc(sizeof(char) * strlen(str));
    int i = 0;

    if (!dest)
        return NULL;
    for (size_t j = 1; j < strlen(str) - 1; i++, j++)
        dest[i] = str[j];
    dest[i] = '\0';
    return dest;
}