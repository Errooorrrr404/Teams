/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** struct_server
*/

#ifndef STRUCT_SERVER_H_
#define STRUCT_SERVER_H_

#define MAX_CLIENTS 100

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/select.h>
#include <stdbool.h>

typedef struct client_s {
    char *ip;
    int id;
    char *command;
    int socket;
    struct sockaddr_in address;
    int len_address;
    bool is_connected;
    bool have_username;
    bool have_password;
    char *username;
    char *uuid;
    bool have_uuid;
    char *password;
    int shutdown;
    char **message_array;
    int have_message_to_free;
    bool use_defined;
    bool use_is_team;
    char *use_team;
    bool use_is_channel;
    char *use_channel;
    bool use_is_thread;
    char *use_thread;
} client_t;

typedef struct server_s {
    char *ip;
    int port;
    int socket_server;
    struct sockaddr_in address;
    int len_address;
    fd_set read_fds;
    fd_set write_fds;
    fd_set except_fds;
} my_server_t;

#endif /* !STRUCT_SERVER_H_ */
