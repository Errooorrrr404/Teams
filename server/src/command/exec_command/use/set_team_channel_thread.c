/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** set_team_channel_thread
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

int set_value_thread(client_t *client, char *uuid_name)
{
    client->use_thread = strdup(uuid_name);
    if (!client->use_thread) {
        send_error_to_client(client, 500, "Error when searching in database.");
        return -1;
    }
    if (client->use_thread[strlen(client->use_thread) - 1] == ' ')
        client->use_thread[strlen(client->use_thread) - 1] = '\0';
    client->use_is_thread = true;
    client->use_defined = true;
    return 0;
}

int check_uuid_thread(char *path, char *uuid)
{
    char *file = concat_path(path, "/description");
    char *uuid_file;

    if (!file)
        return -1;
    uuid_file = get_last_line(file);
    free(file);
    if (!uuid_file)
        return -1;
    if (strncmp(uuid, uuid_file, strlen(uuid)) == 0) {
        free(uuid_file);
        return 0;
    }
    free(uuid_file);
    return -1;
}

int select_threads_in_databse(client_t *client, char *uuid_name, DIR *dir,
char *folder)
{
    struct stat s;
    struct dirent *my_dir;
    char *path;

    while ((my_dir = readdir(dir)) != NULL) {
        if (strstr(my_dir->d_name, uuid_name))
            return set_value_thread(client, uuid_name);
        path = concat_path(folder, my_dir->d_name);
        if (!path)
            return -1;
        printf("%s\n", path);
        stat(path, &s);
        if (S_ISDIR(s.st_mode) == 1 &&
        check_uuid_thread(path, uuid_name) == 0) {
            free(path);
            return set_value_thread(client, my_dir->d_name);
        }
        free(path);
    }
    return 84;
}

int search_thread_in_database(client_t *client, char *uuid_name)
{
    DIR *dir;
    int my_return = 0;
    char *path = concat_path("./server/files/database/data/", client->use_team);
    char *path2;

    path = my_concat_path(path, '/', client->use_channel);
    path2 = concat_path(path, "/");
    free(path);
    if (!path2)
        return -1;
    dir = opendir(path2);
    if (!dir) {
        free(path2);
        return -1;
    }
    my_return = select_threads_in_databse(client, uuid_name, dir, path2);
    closedir(dir);
    free(path2);
    return my_return;
}

void set_team_channel_thread(client_t *client, char **array)
{
    int my_error = 0;

    free_and_unset_use(client);
    if (array[1][strlen(array[1]) - 1] == ' ')
        array[1][strlen(array[1]) - 1] = '\0';
    if (array[2][strlen(array[2]) - 1] == ' ')
        array[2][strlen(array[2]) - 1] = '\0';
    if (array[3][strlen(array[3]) - 1] == ' ')
        array[3][strlen(array[3]) - 1] = '\0';
    my_error = search_team_in_database(client, array[1]);
    if (my_error == 0) {
        my_error = search_channel_in_database(client, array[2]);
        check_display_team_channel_thread(client, array, my_error);
    } else if (my_error == -1) {
        send_to_client(client, 500, "Error when searching in database.");
        free_and_unset_use(client);
    } else {
        send_to_client(client, 500, "The team doesn't exist.");
        free_and_unset_use(client);
    }
}