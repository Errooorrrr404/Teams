/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** my_client
*/

#include <fcntl.h>
#include "struct_client.h"
#include "include_client.h"
#include "logging_client.h"

void free_client(my_client_t *client)
{
    if (client->have_username == true)
        free(client->username);
    if (client->have_uuid == true)
        free(client->uuid);
    free(client->ip_server);
    free(client);
}

int init_client(my_client_t *client, char *ip, char *port)
{
    if (strcmp(ip, "localhost") == 0)
        client->ip_server = strdup("127.0.0.1");
    else
        client->ip_server = strdup(ip);
    if (!client->ip_server)
        return -1;
    client->port_server = atoi(port);
    if (client->port_server <= 0) {
        free(client->ip_server);
        return -1;
    }
    client->have_username = false;
    client->have_uuid = false;
    return 0;
}

int setup_client(my_client_t *client)
{
    client->socket_server = socket(AF_INET, SOCK_STREAM, 0);
    if (client->socket_server == -1) {
        printf("Can't create a socket...\n");
        return 84;
    } else
        printf("Socket successfully created..\n");
    bzero(&client->servaddr, sizeof(client->servaddr));
    client->servaddr.sin_family = AF_INET;
    client->servaddr.sin_addr.s_addr = inet_addr(client->ip_server);
    client->servaddr.sin_port = htons(client->port_server);
    if (connect(client->socket_server, (struct sockaddr *)&client->servaddr,
        sizeof(client->servaddr)) != 0) {
        printf("Can't connect to the server...\n\n");
        free(client->ip_server);
        return -1;
    } else
        printf("connected to the server...\n\n");
    return 0;
}

int my_client(char *ip, char *port)
{
    my_client_t *client = malloc(sizeof(my_client_t));

    int flag = fcntl(STDIN_FILENO, F_GETFL, 0);

    flag |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flag);
    if (!client)
        return 84;
    if (init_client(client, ip, port) == -1) {
        free(client);
        return 84;
    }
    if (setup_client(client) == -1) {
        free(client);
        return 84;
    }
    loop(client, 0);
    close(client->socket_server);
    free_client(client);
    return 0;
}