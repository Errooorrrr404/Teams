/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** struct_client
*/

#ifndef STRUCT_CLIENT_H_
#define STRUCT_CLIENT_H_

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include "logging_client.h"

typedef struct my_client_s {
    char *path_default;
    char *ip_client;
    char *ip_server;
    int port_server;
    int socket_server;
    struct sockaddr_in servaddr;
    fd_set read_fds;
    fd_set write_fds;
    fd_set except_fds;

    int id;
    bool is_connected;
    bool have_username;
    char *username;
    bool have_uuid;
    char *uuid;
} my_client_t;

// client_channel_print_threads
// client_error_unauthorized
// client_error_unknown_channel
// client_error_unknown_team
// client_error_unknown_thread
// client_error_unknown_user
// client_event_loggedin
// client_event_private_message_received
// client_event_thread_message_received
// client_print_teams
// client_print_users
// client_private_message_print_messages
// client_team_print_channels
// client_thread_print_replies

#endif /* !STRUCT_CLIENT_H_ */
