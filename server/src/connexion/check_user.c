/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** check_account_exist
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
#include <sys/stat.h>
#include "struct_server.h"
#include "include.h"

char *get_file(client_t *client)
{
    int fd = open("server/files/access.config", O_RDONLY);
    struct stat fichier;
    int nb = stat("server/files/access.config", &fichier);
    char *file;

    if (fd == -1 || nb == -1) {
        send_to_client(client, 404, "Internal Error config file not found.");
        return NULL;
    }
    file = malloc(sizeof(char) * (fichier.st_size + 1));
    if (!file) {
        close(fd);
        return NULL;
    }
    nb = read(fd, file, fichier.st_size);
    file[nb] = '\0';
    close(fd);
    return file;
}

int find_user(char *file, char *concat)
{
    char *path;

    if (!file)
        return -1;
    if (strstr(file, concat) != NULL) {
        path = concat_path("./server/files/database/users/", concat);
        if (!path) {
            free(file);
            return 0;
        }
        free(file);
        if (access(path, R_OK) == 0) {
            free(path);
            return 1;
        }
        free(path);
        return 0;
    }
    free(file);
    return 0;
}

void connect_and_setup_client(client_t *client, client_t *list_client)
{
    client->uuid = recup_uuid_client(client->username);
    if (!client->uuid) {
        send_to_client(client, 530, "Error when connecting client.");
        client->is_connected = false;
        client->have_username = false;
        free (client->username);
    } else {
        client->is_connected = true;
        client->have_uuid = true;
        dprintf(client->socket, "%d %s\n%s\n%s", 230,
        "User logged in, proceed.", client->username, client->uuid);
        printf("[MY_TEAMS EPITECH] Client [%d] ", client->id);
        server_event_user_logged_in(client->uuid);
        for (int i = 0; i != MAX_CLIENTS; i++) {
            if (list_client[i].is_connected == true &&
            list_client[i].socket != client->socket)
                dprintf(list_client[i].socket, "400\n%s\n%s", client->uuid,
                client->username);
        }
    }
}

void create_user(client_t *client)
{
    int fd = open("./server/files/access.config", O_CREAT | O_RDWR | O_APPEND,
    S_IRUSR | S_IWUSR);
    char *uuid;

    if (fd == -1) {
        send_to_client(client, 500, "Error when checking user.");
        return;
    }
    dprintf(fd, "%s\n", client->username);
    close(fd);
    uuid = create_uuid_client(client->username);
    if (!uuid) {
        send_to_client(client, 500, "Error when checking user.");
        return;
    }
    server_event_user_created(uuid, client->username);
    server_event_user_loaded(uuid, client->username);
    free(uuid);
}

int check_account(client_t *client, client_t *list_client)
{
    char *file = get_file(client);
    int is_finded = find_user(file, client->username);

    if (is_finded == 1) {
        connect_and_setup_client(client, list_client);
    } else {
        create_user(client);
        connect_and_setup_client(client, list_client);
    }
    return 0;
}