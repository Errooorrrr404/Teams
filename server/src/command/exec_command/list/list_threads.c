/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list_threads
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

void display_info_list_threads(client_t *client, char *list_threads)
{
    dprintf(client->socket, "%d %s\n%s\n", 200, "Command Okay.", list_threads);
    printf("[MY_TEAMS EPITECH] Client [%d] ", client->id);
    printf("\033[32m[Response] %d %s\033[0m\n", 200, "Command Okay.");
}

char *concat_threads(char *list_threads, struct dirent *my_dir, DIR *dir,
client_t *client)
{
    list_threads = my_concat(list_threads, my_dir->d_name);
    if (!list_threads) {
        closedir(dir);
        send_error_to_client(client, 500, "Error when listing threads.");
        return NULL;
    }
    list_threads = my_concat(list_threads, " ");
    if (!list_threads) {
        closedir(dir);
        send_error_to_client(client, 500, "Error when listing threads.");
        return NULL;
    }
    return list_threads;
}

void print_threads(client_t *client, DIR *dir, char *list_threads)
{
    struct dirent *my_dir;

    while ((my_dir = readdir(dir)) != NULL) {
        if (my_dir->d_name[0] != '.' &&
        strcmp(my_dir->d_name, "reply") != 0 &&
        strcmp(my_dir->d_name, "description") != 0) {
            list_threads = concat_threads(list_threads, my_dir, dir, client);
            if (!list_threads)
                return;
        }
    }
    display_info_list_threads(client, list_threads);
    closedir(dir);
}

int list_threads_exist(client_t *client , char *list_thread, DIR *dir,
char *folder)
{
    if (!list_thread) {
        closedir(dir);
        free(folder);
        send_error_to_client(client, 500, "Error when listing thread.");
        return 84;
    }
    return 0;
}

void list_threads(client_t *client)
{
    DIR *dir;
    char *list_thread;
    char *folder = concat_path("./server/files/database/data/",
    client->use_team);

    if (!folder)
        return;
    folder = my_concat_path(folder, '/', client->use_team);
    if (!folder) {
        send_error_to_client(client, 500, "Error when listing thread.");
        return;
    }
    dir = opendir(folder);
    if (dir_threads_is_exist(dir, folder, client) == 84)
        return;
    list_thread = strdup("List of thread:");
    if (list_threads_exist(client, list_thread, dir, folder) == 84)
        return;
    print_threads(client, dir, list_thread);
}