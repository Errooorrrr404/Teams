/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** set_team
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

int set_value_team(client_t *client, char *uuid_name)
{
    client->use_team = strdup(uuid_name);
    if (!client->use_team) {
        send_error_to_client(client, 500, "Error when searching in database.");
        return -1;
    }
    if (client->use_team[strlen(client->use_team) - 1] == ' ')
        client->use_team[strlen(client->use_team) - 1] = '\0';
    client->use_is_team = true;
    client->use_defined = true;
    return 0;
}

int check_uuid(char *path, char *uuid)
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

int select_teams_in_databse(client_t *client, char *uuid_name, DIR *dir)
{
    struct stat s;
    struct dirent *my_dir;
    char *path;

    while ((my_dir = readdir(dir)) != NULL) {
        if (strstr(my_dir->d_name, uuid_name))
            return set_value_team(client, uuid_name);
        path = concat_path("./server/files/database/data/", my_dir->d_name);
        if (!path)
            return -1;
        stat(path, &s);
        if (S_ISDIR(s.st_mode) == 1 && check_uuid(path, uuid_name) == 0) {
            free(path);
            return set_value_team(client, my_dir->d_name);
        }
        free(path);
    }
    return 84;
}

int search_team_in_database(client_t *client, char *uuid_name)
{
    DIR *dir = opendir("./server/files/database/data/");
    int my_return = 0;

    if (!dir)
        return -1;
    my_return = select_teams_in_databse(client, uuid_name, dir);
    closedir(dir);
    return my_return;
}

void set_team(client_t *client, char **array)
{
    int nb = 0;

    free_and_unset_use(client);
    if (array[1][strlen(array[1]) - 1] == ' ')
        array[1][strlen(array[1]) - 1] = '\0';
    nb = search_team_in_database(client, array[1]);
    if (nb == -1)
        send_to_client(client, 500, "Error when searching in database.");
    else if (nb == 0)
        send_to_client(client, 200, "Command Okay.");
    else {
        send_to_client(client, 500, "The team doesn't exist.");
        free_and_unset_use(client);
    }
}