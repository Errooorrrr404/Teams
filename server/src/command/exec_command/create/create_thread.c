/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_thread
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

int create_reply_file(char *path_folder)
{
    char *file = concat_path(path_folder, "/reply");
    int fd;

    if (!file)
        return -1;
    fd = open(file, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1)
        return -1;
    close(fd);
    return 0;
}

void add_thread(client_t *client, char **array, char *folder)
{
    char *description = concat_path(folder, "/description");

    if (!description) {
        send_error_to_client(client, 500, "Error when creating thread.");
        return;
    }
    if (write_in_file(client, description, array[1], array[2]) == -1 ||
    log_server_thread_created(client, array[1], array[2]) == -1) {
        free(description);
        send_error_to_client(client, 500, "Error when creating thread.");
        return;
    }
    if (create_reply_file(folder) == -1) {
        free(description);
        send_error_to_client(client, 500, "Error when creating thread.");
        return;
    }
    free(description);
    send_to_client(client, 200, "thread Created.");
}

void create_thread_2(client_t *client, char *folder, char **array)
{
    struct stat s;
    int fd;

    if (stat(folder, &s)  != -1) {
        send_error_to_client(client, 520, "The thread already exists.");
    } else {
        fd = mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (fd == -1) {
            send_error_to_client(client, 500, "Error when creating thread.");
        } else
            add_thread(client, array, folder);
    }
}

void create_thread(client_t *client, char **array)
{
    char *folder = concat_path("./server/files/database/data/",
    client->use_team);

    if (!folder) {
        send_error_to_client(client, 500, "Error when creating thread.");
        return;
    }
    folder = my_concat_path(folder, '/', client->use_channel);
    if (!folder) {
        send_error_to_client(client, 500, "Error when creating thread.");
        return;
    }
    folder = my_concat_path(folder, '/', array[1]);
    if (!folder) {
        send_error_to_client(client, 500, "Error when creating thread.");
        return;
    }
    create_thread_2(client, folder, array);
    free(folder);
}