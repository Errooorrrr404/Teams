/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** is_good_argument
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
#include <sys/types.h>
#include <dirent.h>
#include "struct_server.h"
#include "include.h"

int is_good_argument(char **array, int loop)
{
    for (int i = 1; i < loop; i++) {
        if (array[i][0] != '\"' || array[i][strlen(array[i]) - 1] != '\"')
            return -1;
    }
    return 0;
}

char **init_array(void)
{
    char **array = malloc(sizeof(char *) * MAX_CLIENTS);

    if (!array)
        return NULL;
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        array[i] = strdup("NULL");
        if (!array[i])
            return NULL;
    }
    return array;
}

char *concat_path(char *path, char *file)
{
    char *str = malloc(sizeof(char) * (strlen(path) + strlen(file) + 2));
    size_t i = 0;

    if (!str)
        return NULL;
    for (size_t j = 0; j < strlen(path); i++, j++)
        str[i] = path[j];
    for (size_t j = 0; j < strlen(file); i++, j++)
        str[i] = file[j];
    str[i] = '\0';
    return str;
}

char *conc_mess(char *path, char *str_1, char *str_2)
{
    size_t len = strlen(path) + strlen(str_1) + strlen(str_2) + 3;
    char *str = malloc(sizeof(char) * (len));
    size_t i = 0;

    if (!str)
        return NULL;
    for (size_t j = 0; j < strlen(path); i++, j++)
        str[i] = path[j];
    for (size_t j = 0; j < strlen(str_1); i++, j++)
        str[i] = str_1[j];
    str[i] = '_';
    i++;
    for (size_t j = 0; j < strlen(str_2); i++, j++)
        str[i] = str_2[j];
    str[i] = '\0';
    return str;
}

int dir_threads_is_exist(DIR *dir, char *folder, client_t *client)
{
    if (!dir) {
        free(folder);
        send_error_to_client(client, 500, "Error when listing thread.");
        return 84;
    }
    return 0;
}