/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** unsubscribe_log
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

void unsubscribe_log(client_t *client)
{
    char *path = concat_path("./server/files/database/data/", client->use_team);
    char *uuid;

    if (!path)
        return;
    path = my_concat_path(path, '/', "description");
    if (!path)
        return;
    uuid = get_last_line(path);
    if (!uuid) {
        free(path);
        return;
    }
    if (uuid[strlen(uuid) - 1] != '\0')
        uuid[strlen(uuid) - 1] = '\0';
    server_event_user_leave_a_team(uuid, client->uuid);
}