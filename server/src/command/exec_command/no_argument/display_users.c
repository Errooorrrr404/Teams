/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** display_users
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
#include "struct_server.h"
#include "include.h"

void send_users_connected(client_t *client, char *users)
{
    if (!users)
        send_error_to_client(client, 500, "Error when loaded clients.");
    else {
        send_to_client(client, 210, users);
        free(users);
    }
}

char *concat_users(char *tmp, char *users, char *uuid)
{
    int len = strlen(users) + strlen(uuid) + strlen(tmp) + 4;
    char *str = malloc(sizeof(char) * (len));
    int i = 0;

    if (!str)
        return NULL;
    for (size_t j = 0; j < strlen(tmp); i++, j++)
        str[i] = tmp[j];
    str[i] = '\n';
    i++;
    for (size_t j = 0; j < strlen(users); i++, j++)
        str[i] = users[j];
    str[i] = '\n';
    i++;
    for (size_t j = 0; j < strlen(uuid); i++, j++)
        str[i] = uuid[j];
    str[i] = '\n';
    str[i + 1] = '\0';
    free(tmp);
    return str;
}

char *set_concat_user(client_t *list_client, char *name, char *uuid,
char *my_concat_user)
{
    int error = 1;

    my_concat_user = concat_users(my_concat_user, name, uuid);
    if (!my_concat_user)
        return NULL;
    my_concat_user[strlen(my_concat_user) - 1] = '\0';
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (list_client[i].is_connected == true) {
            if (strstr(list_client[i].username, name)) {
                my_concat_user = my_concat_path(my_concat_user, '\n', "1\n");
                error = 0;
                break;
            }
        }
    }
    if (error == 1)
        my_concat_user = my_concat_path(my_concat_user, '\n', "0\n");
    return my_concat_user;
}

char *concat_list_users(char *name, char *my_concat_user, client_t *list_client)
{
    char *path = concat_path("./server/files/database/users/", name);
    char *uuid;

    if (!path)
        return NULL;
    uuid = get_last_line(path);
    if (!uuid)
        return NULL;
    uuid[strlen(uuid) - 1] = '\0';
    my_concat_user = set_concat_user(list_client, name, uuid, my_concat_user);
    my_concat_user[strlen(my_concat_user) - 1] = '\0';
    free(uuid);
    free(path);
    return my_concat_user;
}

void display_users(client_t *client, client_t *list_client)
{
    char *my_concat_user = strdup("List of users:");
    DIR *dir;
    struct dirent *my_dir;

    if (!my_concat_user)
        return;
    dir = opendir("./server/files/database/users/");
    while ((my_dir = readdir(dir)) != NULL) {
        if (my_dir->d_name[0] != '.') {
            my_concat_user = concat_list_users(my_dir->d_name, my_concat_user,
            list_client);
            if (!my_concat_user)
                return;
        }
    }
    closedir(dir);
    send_users_connected(client, my_concat_user);
}