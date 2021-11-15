/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** get_uuid_thread
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

char *get_uuid_channel_for_thread(client_t *client)
{
    char *folder = concat_path("./server/files/database/data/",
    client->use_team);
    char *uuid;

    if (!folder)
        return NULL;
    folder = my_concat_path(folder, '/', client->use_channel);
    if (!folder)
        return NULL;
    folder = my_concat_path(folder, '/', "description");
    if (!folder)
        return NULL;
    uuid = get_last_line(folder);
    free(folder);
    if (!uuid)
        return NULL;
    return uuid;
}

char *get_uuid_thread(client_t *client, char *name_thread)
{
    char *folder = concat_path("./server/files/database/data/",
    client->use_team);
    char *uuid;

    if (!folder)
        return NULL;
    folder = my_concat_path(folder, '/', client->use_channel);
    if (!folder)
        return NULL;
    folder = my_concat_path(folder, '/', name_thread);
    if (!folder)
        return NULL;
    folder = my_concat_path(folder, '/', "description");
    if (!folder)
        return NULL;
    uuid = get_last_line(folder);
    free(folder);
    if (!uuid)
        return NULL;
    return uuid;
}

int log_server_thread_created(client_t *client, char *name_thread,
char *message)
{
    char *uuid_channel = get_uuid_channel_for_thread(client);
    char *uuid_thread;

    if (!uuid_channel)
        return -1;
    uuid_thread = get_uuid_thread(client, name_thread);
    if (!uuid_thread) {
        free(uuid_channel);
        return -1;
    }
    if (uuid_thread[strlen(uuid_thread) - 1] == '\n')
        uuid_thread[strlen(uuid_thread) - 1] = '\0';
    if (uuid_channel[strlen(uuid_channel) - 1] == '\n')
        uuid_channel[strlen(uuid_channel) - 1] = '\0';
    server_event_thread_created(uuid_channel, uuid_thread, client->uuid,
    message);
    free(uuid_channel);
    free(uuid_thread);
    return 0;
}