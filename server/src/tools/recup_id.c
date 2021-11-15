/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** recup_id
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <uuid/uuid.h>
#include <unistd.h>
#include "include.h"

char *set_uuid_client(int fd)
{
    uuid_t binuuid;
    char *uuid;
    uuid_generate_random(binuuid);

    uuid = malloc(sizeof(char) * 37);
    if (!uuid) {
        close(fd);
        return NULL;
    }
    uuid_unparse(binuuid, uuid);
    dprintf(fd, "%s\n", uuid);
    close(fd);
    return uuid;

}

char *create_uuid_client(char *name)
{
    char *path = concat_path("./server/files/database/users/", name);
    int fd;
    char *uuid;

    if (!path)
        return NULL;
    if (access(path, R_OK) == 0) {
        uuid = get_last_line(path);
        free(path);
        if (!uuid)
            return NULL;
        return uuid;
    }
    fd = open(path , O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        free(path);
        return NULL;
    }
    free(path);
    return set_uuid_client(fd);
}

char *extract_uuid_client(char *path)
{
    struct stat s;
    int fd = open(path , O_RDONLY);
    char *uuid;
    int nb = 0;

    if (fd == -1) {
        free(path);
        return NULL;
    }
    stat(path, &s);
    uuid = malloc(sizeof(char) * (s.st_size + 1));
    if (!uuid) {
        close(fd);
        return NULL;
    }
    nb = read(fd, uuid, s.st_size);
    uuid[nb - 1] = '\0';
    free(path);
    close(fd);
    return uuid;
}

char *recup_uuid_client(char *name)
{
    char *path = concat_path("./server/files/database/users/", name);

    if (path == NULL)
        return NULL;
    if (access(path, R_OK) == -1) {
        free(path);
        return NULL;
    }
    return extract_uuid_client(path);
}

char *get_username_from_uuid(client_t *list_client, char *uuid)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (strcmp(uuid, list_client[i].username) == 0 ||
        strcmp(uuid, list_client[i].uuid) == 0) {
            return strdup(list_client[i].username);
        }
    }
    return strdup("badlogin");
}