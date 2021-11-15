/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** include_client
*/

#ifndef INCLUDE_CLIENT_H_
#define INCLUDE_CLIENT_H_

#include <stdlib.h>
#include "struct_client.h"
// my_client.c
int my_client(char *ip, char *port);

int is_shutdown(char *input, my_client_t *client);
void loop(my_client_t *client, int nb);
int get_code(char *message);
int analyse_code(my_client_t *client, int code, char *message);
char *get_message(char *my_read, int nb);
int command_is_accepted(my_client_t *client, int code, char *message);
int command_is_temporary_refused(int code, char *message);
int command_is_refused(int code, char *message);
int print_message(char *message, int my_return);
char **str_to_array(char *str, char delimiter);
void free_array(char **array);
char *clean_str(char *str);

int listen_write_server(my_client_t *client, int nb);
int listen_read_server(my_client_t *client, int nb);
int print_users(char *message, int my_return);
int print_list(char *message, int my_return, int code);
int display_list_message(char *message, int my_return);
int accepted_and_data_transfert(my_client_t *client, char *message, int code);
void setup_data_client(my_client_t *client, char *message);
int display_new_user_connected(char *message);
int display_user_disconnected(char *message);


#endif /* !INCLUDE_CLIENT_H_ */
