/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** display_messages
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

void display_message_in_log(char *message, client_t *client, char *str)
{
    if (!message) {
        send_error_to_client(client, 500, "Error when getting message.");
        return;
    }
    dprintf(client->socket, "204 %s", str);
    printf("[MY_TEAMS EPITECH] Client [%d] ", client->id);
    printf("\033[32m[Response] %d %s\033[0m\n", 200, "Command Okay.");
    free(message);
    free(str);
}

void display_messages_user(client_t *client, int fd, char *file)
{
    char *message = strdup("List of messages:\n");
    struct stat s;
    char *str;
    int nb = 0;

    stat(file, &s);
    str = malloc(sizeof(char) * (s.st_size + 1));
    if (!str) {
        send_error_to_client(client, 500, "Error when getting message.");
        return;
    }
    nb = read(fd, str, s.st_size);
    str[nb] = '\0';
    close(fd);
    display_message_in_log(message, client, str);
}

void analyse_messages_user(char **array, client_t *client, char *path)
{
    int fd = access(path, W_OK);
    char *path2;

    if (fd == -1) {
        path2 = conc_mess("./server/files/database/messages/", array[1],
        client->username);
        if (!path2) {
            send_error_to_client(client, 500, "Error when getting message.");
            free_array(array);
            return;
        }
        fd = open(path2, O_RDONLY);
        free(path);
        display_messages_user(client, fd, path2);
    } else
        fd = open(path, O_RDONLY);
    free_array(array);
    display_messages_user(client, fd, path);
}

int check_errors_messages(void *str, client_t *client, char *tmp)
{
    char *path;

    if (!str) {
        send_to_client(client, 500, "Error when getting message to user");
        return 84;
    }
    path = conc_mess("./server/files/database/messages/", tmp,
    client->username);
    if (!path) {
        send_to_client(client, 500, "Error when getting message to user");
        return -1;
    }
    if (access(path, F_OK) == -1) {
        free(path);
        return -1;
    }
    free(path);
    return 0;
}

void display_messages(client_t *client, char *command)
{
    char **array = command_to_array(command, client);
    char *path1;

    if (check_errors_messages(array, client, array[1]) == 84)
        return;
    if (array[1][strlen(array[1]) - 1] == ' ')
        array[1][strlen(array[1]) - 1] = '\0';
    path1 = conc_mess("./server/files/database/messages/",
    client->username, array[1]);
    if (check_errors_messages(path1, client, array[1]) == -1) {
        free(path1);
        free_array(array);
        return;
    }
    analyse_messages_user(array, client, path1);
    free(path1);
}
