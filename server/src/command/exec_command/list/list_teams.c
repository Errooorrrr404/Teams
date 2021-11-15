/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list_teams
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

void display_info_list_teams(client_t *client, char *list_teams)
{
    dprintf(client->socket, "%d %s\n%s\n", 205, "Command Okay.", list_teams);
    printf("[MY_TEAMS EPITECH] Client [%d] ", client->id);
    printf("\033[32m[Response] %d %s\033[0m\n", 205, "Command Okay.");
    free(list_teams);
}

char *concat_info_team(char *list_teams, char *name_team, char *uuid,
char *desc_team)
{
    char *str = concat_path(list_teams, name_team);

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
    free(list_teams);
    free(uuid);
    free(desc_team);
    return str;
}

char *get_info_teams(char *list_teams, char *name_team, char *path_team)
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
    return concat_info_team(list_teams, name_team, uuid, desc_team);
}

void print_teams(client_t *client, DIR *dir, char *list_teams)
{
    struct dirent *my_dir;
    char *path;

    while ((my_dir = readdir(dir)) != NULL) {
        if (my_dir->d_name[0] != '.' &&
        strcmp(my_dir->d_name, "access.config") != 0 &&
        strcmp(my_dir->d_name, "description") != 0) {
            path = concat_path("./server/files/database/data/", my_dir->d_name);
            if (!path) {
                send_error_to_client(client, 500, "Error when listing teams.");
                return;
            }
            list_teams = get_info_teams(list_teams, my_dir->d_name, path);
            if (!list_teams)
                return;
            free(path);
        }
    }
    display_info_list_teams(client, list_teams);
}

void list_teams(client_t *client)
{
    DIR *dir;
    char *list_teams;

    dir = opendir("./server/files/database/data/");
    if (!dir) {
        send_error_to_client(client, 500, "Error when listing teams.");
        return;
    }
    list_teams = strdup("List of teams:\n");
    if (!list_teams) {
        closedir(dir);
        send_error_to_client(client, 500, "Error when listing teams.");
        return;
    }
    print_teams(client, dir, list_teams);
    closedir(dir);
}