/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_message_to_user
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

void send_info_user(char **array, client_t *client, client_t *list_client,
int fd)
{
    time_t timestamp = time(NULL);

    dprintf(fd, "From\n%s\n%ld\n%s\n", array[1],
    timestamp, array[2]);
    dprintf(client->socket, "%d %s\n", 200, "Message send.");
    dprintf(list_client->socket, "From\n%s\n%ld\n%s\n", client->username,
    timestamp, array[2]);
    printf("[MY_TEAMS EPITECH] Client [%d] \033[32m[Response] %d %s\033[0m\n",
    client->id, 200, "Message Send");
    printf("message from %s to %s: %s\n", client->username,
    list_client->username, array[2]);
    server_event_private_message_sended(client->uuid, list_client->uuid,
    array[2]);

}

void find_user_messages(char **array, client_t *client, client_t *list_client,
int fd)
{
    int error = 1;
    int time = 0;

    for (int i = 0; list_client[i].socket != -1; i++) {
        if (list_client[i].have_username == true &&
        strcmp(array[1], list_client[i].username) == 0) {
            if (time == 0) {
                send_info_user(array, client, &list_client[i], fd);
                time++;
            } else
                send_without_log_history(array, client, &list_client[i]);
            error = 0;
        }
    }
    close(fd);
    free_array(array);
    if (error == 1)
        send_error_to_client(client, 500, "Invalid username");
}

int check_access(client_t *client, char **array, int fd)
{
    if (fd == -1) {
            send_error_to_client(client, 500, "Error when sending message.");
            free_array(array);
            return -1;
    }
    return 0;
}

void send_the_message(char **array, client_t *client, client_t *list_client,
char *path)
{
    int fd = access(path, W_OK);
    char *path2;

    if (fd == -1) {
        path2 = conc_mess("./server/files/database/messages/", array[1],
        client->username);
        if (!path2) {
            send_error_to_client(client, 500, "Error when sending message.");
            free_array(array);
            return;
        }
        fd = open(path2, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
        free(path2);
        if (check_access(client, array, fd) == -1)
            return;
    } else
        fd = open(path, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    find_user_messages(array, client, list_client, fd);
}

void send_message_to_user(client_t *client, char *command,
client_t *list_client)
{
    char **array = command_to_array(command, client);
    char *path1;
    char *username = get_username_from_uuid(list_client, array[1]);

    if (!array || !username)
        return;
    free(array[1]);
    array[1] = strdup(username);
    if (!array[1])
        return;
    path1 = conc_mess("./server/files/database/messages/",
    client->username, array[1]);
    if (!path1) {
        send_error_to_client(client, 500, "Error when sending message.");
        free_array(array);
        return;
    }
    send_the_message(array, client, list_client, path1);
    free(path1);
    free(username);
}