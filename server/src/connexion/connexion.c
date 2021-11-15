/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** connexion
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

void print_new_client(int i, struct sockaddr_in client_addr)
{
    printf("[MY_TEAMS EPITECH] \033[33mNew Client: ip %s, port %d",
    inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    printf(", id %d\033[0m\n", i);
}

void set_up_client(client_t *client)
{
    client->have_username = false;
    client->have_password = false;
    client->shutdown = 0;
    client->message_array = init_array();
    client->use_defined = false;
    client->use_is_team = false;
    client->use_is_channel = false;
    client->use_is_thread = false;
    client->have_uuid = false;
}

int added_in_struct(client_t *client, int new_sock,
struct sockaddr_in client_addr, socklen_t client_len)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client[i].socket == -1) {
            client[i].socket = new_sock;
            client[i].address = client_addr;
            client[i].len_address = client_len;
            client[i].id = i;
            set_up_client(&client[i]);
            if (!client[i].message_array)
                break;
            print_new_client(i, client_addr);
            return 0;
        }
    }
    return -1;
}

int connection(my_server_t *server, client_t *client)
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int new_sock = accept(server->socket_server,
    (struct sockaddr *)&client_addr, &client_len);
    int is_in_sctruct = 0;

    memset(&client_addr, 0, sizeof(client_addr));
    getpeername(new_sock, (struct sockaddr *)&client_addr,
    (socklen_t *)&client_len);
    if (new_sock < 0) {
        my_message_server("accept failed", 84);
        return -1;
    }
    dprintf(new_sock, "220 Service ready for new user.\n");
    is_in_sctruct = added_in_struct(client, new_sock, client_addr, client_len);
    if (is_in_sctruct == -1) {
        printf("There is too much connections. Close new connection.\n");
        close(new_sock);
    }
    return is_in_sctruct;
}

void connect_client(client_t *client, char *command, client_t *list_client)
{
    char **array = command_to_array(command, client);

    if (!array) {
        send_error_to_client(client, 500, "Error when loaded command");
        return;
    }
    if (client->have_username == false)
        set_username(client, command);
    if (client->have_username == true)
        check_account(client, list_client);
    free_array(array);
}