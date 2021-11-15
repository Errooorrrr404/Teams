/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list_channels
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <dirent.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "struct_server.h"
#include "include.h"

void display_info_list_channels(client_t *client, char *list_channels)
{
    dprintf(client->socket, "%d %s\n%s\n", 206, "Command Okay.", list_channels);
    printf("[MY_channels EPITECH] Client [%d] ", client->id);
    printf("\033[32m[Response] %d %s\033[0m\n", 206, "Command Okay.");
    free(list_channels);
}

char *concat_info_channel(char *list_channels, char *name_team, char *uuid,
char *desc_team)
{
    char *str = concat_path(list_channels, name_team);

    if (!str)
        return NULL;
    str = my_concat_path(str, '\n', uuid);
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
    if (!str)
        return NULL;
    str = my_concat_path(str, '\n', desc_team);
    if (!str)
        return NULL;
    free(list_channels);
    free(uuid);
    free(desc_team);
    return str;
}

char *get_info_channels(char *list_channels, char *name_team, char *path_team)
{
    char *description = concat_path(path_team, "/description");
    char *uuid;
    char *desc_team;

    if (!description)
        return NULL;
    uuid = get_last_line(description);
    if (!uuid) {
        free(description);
        return NULL;
    }
    desc_team = get_first_line(description);
    free(description);
    if (!desc_team) {
        free(uuid);
        return NULL;
    }
    return concat_info_channel(list_channels, name_team, uuid, desc_team);
}

void print_channels(client_t *client, DIR *dir, char *list_channels, char *path)
{
    struct dirent *my_dir;

    while ((my_dir = readdir(dir)) != NULL) {
        if (my_dir->d_name[0] != '.' &&
        strcmp(my_dir->d_name, "access.config") != 0 &&
        strcmp(my_dir->d_name, "description") != 0) {
            path = my_concat_path(path, '/', my_dir->d_name);
            if (!path) {
                send_error_to_client(client, 501,
                "Error when listing channels.");
                return;
            }
            list_channels = get_info_channels(list_channels,
            my_dir->d_name, path);
            if (!list_channels)
                return;
        }
    }
    free(path);
    display_info_list_channels(client, list_channels);
}

void list_channels(client_t *client)
{
    DIR *dir;
    char *list_channels;
    char *path = concat_path("./server/files/database/data/",
    client->use_team);

    if (!path)
        return;
    dir = opendir(path);
    if (!dir) {
        send_error_to_client(client, 500, "Error when listing channels.");
        return;
    }
    list_channels = strdup("List of channels:\n");
    if (!list_channels) {
        closedir(dir);
        send_error_to_client(client, 500, "Error when listing channels.");
        return;
    }
    print_channels(client, dir, list_channels, path);
    closedir(dir);
}