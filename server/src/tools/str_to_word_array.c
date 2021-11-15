/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** str_to_word_array
*/

#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "include.h"
#include "struct_server.h"

int count_nb_delimiter(char *str, char delimiter)
{
    int nb_delimiter = 1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == delimiter)
            nb_delimiter++;
    }
    return (nb_delimiter);
}

int count_size(char *str, char delimiter)
{
    static int i = 0;
    int nb = 0;
    int size = strlen(str);

    for (; str[i] != delimiter && str[i] != '\0' && i <= size; i++, nb++);
    i++;
    if (str[i - 1] == '\0')
        i = 0;
    return (nb + 1);
}

char **my_malloc_array(char **array, char *str, char delimiter, int nb_line)
{
    int my_malloc[nb_line];

    for (int i = 0; i < nb_line; i++) {
        my_malloc[i] = count_size(str, delimiter);
        array[i] = malloc(sizeof(char) * (my_malloc[i] + 1));
        if (!array[i])
            return NULL;
    }
    return (array);
}

char **fill_new_array(char **array, char *str, char delimiter)
{
    int line = 0;
    int col = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == delimiter) {
            array[line][col] = '\0';
            array[line] = clean_str(array[line]);
            col = 0;
            line++;
        } else {
            array[line][col] = str[i];
            col++;
        }
    }
    array[line][col] = '\0';
    return (array);
}

char **str_to_array(char *str, char delimiter)
{
    int nb_line = count_nb_delimiter(str, delimiter);
    char **array = malloc(sizeof(char *) * (nb_line + 1));

    if (!array)
        return NULL;
    array = my_malloc_array(array, str, delimiter, nb_line);
    if (!array)
        return NULL;
    array = fill_new_array(array, str, delimiter);
    array[nb_line] = NULL;
    return (array);
}
