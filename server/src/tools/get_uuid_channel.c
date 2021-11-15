/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** get_uuid_channel
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

char *get_uuid_team_for_channel(client_t *client)
{
    char *folder = concat_path("./server/files/database/data/",
    client->use_team);
    char *uuid;

    if (!folder)
        return NULL;
    folder = my_concat_path(folder, '/', "description");
    if (!folder)
        return NULL;
    uuid = get_last_line(folder);
    if (!uuid) {
        free(folder);
        return NULL;
    }
    free(folder);
    return uuid;
}

char *get_uuid_channel_for_log(client_t *client, char *name)
{
    char *folder = concat_path("./server/files/database/data/",
    client->use_team);
    char *uuid;

    if (!folder)
        return NULL;
    folder = my_concat_path(folder, '/', name);
    if (!folder)
        return NULL;
    folder = my_concat_path(folder, '/', "description");
    if (!folder)
        return NULL;
    uuid = get_last_line(folder);
    if (!uuid) {
        free(folder);
        return NULL;
    }
    free(folder);
    return uuid;
}

void log_channel_in_client(client_t *client, char *uuid_team,
char *uuid_channel, char *channel_name)
{
    if (uuid_team[strlen(uuid_team) - 1] == '\n')
        uuid_team[strlen(uuid_team) - 1] = '\0';
    if (uuid_channel[strlen(uuid_channel) - 1] == '\n')
        uuid_channel[strlen(uuid_channel) - 1] = '\0';
    server_event_channel_created(uuid_team, uuid_channel, channel_name);
}

int log_server_event_channel_created(client_t *client, char *channel_name,
char *description)
{
    char *uuid_team = get_uuid_team_for_channel(client);
    char *uuid_channel;

    if (!uuid_team)
        return -1;
    if (channel_name[strlen(channel_name) - 1] == ' ')
        channel_name[strlen(channel_name) - 1] = '\0';
    uuid_channel = get_uuid_channel_for_log(client, channel_name);
    if (!uuid_channel)
        return -1;
    log_channel_in_client(client, uuid_team, uuid_team, channel_name);
    dprintf(client->socket, "201\n%s\n%s\n%s", uuid_channel, channel_name,
    description);
    free(uuid_team);
    free(uuid_channel);
    return 0;
}