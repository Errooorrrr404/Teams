/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** set_user_pass
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

void set_username(client_t *client, char *command)
{
    char *str;
    char *login;

    if (!strstr(command, "/login")) {
        send_to_client(client, 530, "Please use USER First.");
    } else {
        str = recup_str(command, "/login");
        if (!str)
            return;
        login = str_without_quotes(str);
        if (!login)
            return;
        client->username = strdup(login);
        free(str);
        if (!client->username)
            return;
        client->have_username = true;
        free(login);
    }
}

void set_password(client_t *client, char *command)
{
    char *str;

    if (!strstr(command, "PASS")) {
        send_to_client(client, 530, "Please use PASS with your password.");
    } else {
        str = recup_str(command, "PASS");
        if (!str)
            return;
        client->password = strdup(str);
        free(str);
        if (!client->password)
            return;
        client->have_password = 1;
    }
}