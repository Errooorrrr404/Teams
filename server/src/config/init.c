/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** init
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "struct_server.h"
#include "include.h"
#include "logging_server.h"

int check_error_loaded_client(int error, char *users, char **array)
{
    free_array(array);
    if (error == -1)
        printf("[MY_TEAMS EPITECH] Error loading users.\n");
    free(users);
    return error;
}

int loaded_client_uuid(char *users, int error)
{
    char **array = str_to_array(users, '\n');
    char *tmp;

    if (!array) {
        free(users);
        return -1;
    }
    for (int i = 0; array[i + 1] != NULL; i++) {
        tmp = create_uuid_client(array[i]);
        if (!tmp)
            error = -1;
        if (tmp && tmp[strlen(tmp) - 1] == '\n')
            tmp[strlen(tmp) - 1] = '\0';
        if (tmp) {
            server_event_user_loaded(tmp, array[i]);
            free(tmp);
        }
    }
    return check_error_loaded_client(error, users, array);
}

int loaded_client(void)
{
    int fd = open("./server/files/access.config", O_RDONLY);
    char *users;
    struct stat s;
    int nb = 0;

    if (fd == -1)
        return -1;
    if (stat("./server/files/access.config", &s) == -1) {
        close(fd);
        return -1;
    }
    users = malloc(sizeof(char) * (s.st_size + 1));
    if (!users) {
        close(fd);
        return -1;
    }
    nb = read(fd, users, s.st_size);
    users[nb] = 0;
    close(fd);
    return loaded_client_uuid(users, 0);
}

int init_client(client_t *client)
{
    if (!client)
        return 84;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client[i].socket = -1;
        client[i].shutdown = 0;
        client[i].is_connected = false;
        client[i].use_defined = false;
        client[i].use_is_team = false;
        client[i].use_is_channel = false;
        client[i].use_is_thread = false;
    }
    return 0;
}

int init_server(char *port, my_server_t *server, int opt)
{
    server->port = atoi(port);
    if (server->port <= 0)
        return my_message_server("Invalid Port.", 84);
    server->socket_server = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket_server == 0)
        return my_message_server("Socket failed.", 84);
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(server->port);
    if (setsockopt(server->socket_server, SOL_SOCKET, SO_REUSEADDR,
    &opt, sizeof(int)) < 0)
        return my_message_server("Setsockopt failed.", 84);
    if (bind(server->socket_server, (struct sockaddr *)&server->address,
    sizeof(server->address)) < 0)
        return my_message_server("Bind failed.", 84);
    if (listen(server->socket_server, 100) < 0)
        return my_message_server("Listen failed.", 84);
    server->len_address = sizeof(server->address);
    return 0;
}