/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** replay_thread
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

void add_thread_in_file(client_t *client, char **array, char *path, char *desc)
{
    int fd = open(path, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    char *uuid;

    if (fd == -1) {
        send_error_to_client(client, 500, "Error reply not send.");
    }
    if (array[1][strlen(array[1]) - 1] == ' ')
        array[1][strlen(array[1]) - 1] = '\0';
    dprintf(fd, "From %s: %s\n", client->username, array[1]);
    close(fd);
    printf("%s\n", desc);
    uuid = get_last_line(desc);
    if (uuid[strlen(uuid) - 1] == '\n')
        uuid[strlen(uuid) - 1] = '\0';
    send_to_client(client, 200, "Thread Added.");
    server_event_thread_new_message(uuid, client->uuid, array[1]);
    if (uuid)
        free(uuid);
    free(desc);
}

void reply_to_thread_2(client_t *client, char **array, char *folder)
{
    char *my_desc = concat_path(folder, "/description");

    folder = my_concat_path(folder, '/', "reply");
    if (!folder) {
        send_error_to_client(client, 500, "Error reply not send.");
        return;
    }
    if (!my_desc) {
        send_error_to_client(client, 500, "Error reply not send.");
        return;
    }
    add_thread_in_file(client, array, folder, my_desc);
    free(folder);
}

void reply_to_thread(client_t *client, char **array)
{
    char *folder = concat_path("./server/files/database/data/",
    client->use_team);

    if (!folder) {
        send_error_to_client(client, 500, "Error reply not send.");
        return;
    }
    folder = my_concat_path(folder, '/', client->use_channel);
    if (!folder) {
        send_error_to_client(client, 500, "Error reply not send.");
        return;
    }
    folder = my_concat_path(folder, '/', client->use_thread);
    if (!folder) {
        send_error_to_client(client, 500, "Error reply not send.");
        return;
    }
    reply_to_thread_2(client, array, folder);
}