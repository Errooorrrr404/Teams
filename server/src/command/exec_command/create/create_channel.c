/*
** EPITECH PROJECT, 2020
** NWP_mychannels_2019
** File description:
** create_channel
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "struct_server.h"
#include "include.h"

void add_channel(client_t *client, char **array, char *folder)
{
    char *description = concat_path(folder, "/description");

    if (!description) {
        send_error_to_client(client, 500, "Error when creating channel.");
        return;
    }
    if (write_in_file(client, description, array[1], array[2]) == -1 ||
    log_server_event_channel_created(client, array[1], array[2]) == -1) {
        free(description);
        send_error_to_client(client, 501, "Error when creating channel.");
        return;
    }
    free(description);
}

char *my_concat_path(char *path, char c, char *file)
{
    char *str = malloc(sizeof(char) * (strlen(path) + strlen(file) + 3));
    int i = 0;

    if (!str) {
        free(path);
        return NULL;
    }
    for (size_t j = 0; j < strlen(path); j++, i++)
        str[i] = path[j];
    str[i] = c;
    i++;
    for (size_t j = 0; j < strlen(file); j++, i++)
        str[i] = file[j];
    str[i] = '\0';
    free(path);
    return str;
}

void create_channel_2(client_t *client, char *folder, char **array)
{
    int fd = mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (fd == -1) {
        send_error_to_client(client, 500, "Error when creating channel.");
    } else
        add_channel(client, array, folder);
}

void create_channel(client_t *client, char **array)
{
    struct stat s;
    char *folder = concat_path("./server/files/database/data/",
    client->use_team);

    if (!folder) {
        send_error_to_client(client, 500, "Error when creating channel.");
        return;
    }
    folder = my_concat_path(folder, '/', array[1]);
    if (!folder) {
        send_error_to_client(client, 500, "Error when creating channel.");
        return;
    }
    if (stat(folder, &s) != -1) {
        send_error_to_client(client, 520, "The channel already exists.");
    } else
        create_channel_2(client, folder, array);
    free(folder);
}