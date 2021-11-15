/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** include
*/

#ifndef INCLUDE_H_
#define INCLUDE_H_

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include "struct_server.h"
#include "logging_client.h"
#include "logging_server.h"

//main.c
void help(void);
int main(int ac, char **av);

//recup_commande.c
void analyse_command(client_t *client, char *command, client_t *list_client);
int recup_commande(client_t *client, client_t *global_client);

//analyse_command.c
void analyse_command_client(client_t *client, char *command,
client_t *list_client);

//connexion.c
int connection(my_server_t *server, client_t *client);
void connect_client(client_t *client, char *command, client_t *list_client);

// set_user_pass.c
void set_username(client_t *client, char *command);
void set_password(client_t *client, char *command);

//my_server.c
int loop_server(my_server_t *server, client_t *client);
int my_server(char *port);

//tools.c
int my_message_server(char *message, int return_value);
int size_array(char **array);
char *concat_path(char *path, char *file);
char *get_username_from_uuid(client_t *list_client, char *uuid);

//str_to_array.c
char **str_to_array(char *str, char delimiter);

// build_fd_sets.c
int build_fd_sets(my_server_t *server, client_t *client);

// exit.c
void exit_client(client_t *client);
void free_client(client_t *client);
void free_server(my_server_t *server);
void free_system(my_server_t *server, client_t *client);

// init.c
int init_client(client_t *client);
int init_server(char *port, my_server_t *server, int opt);
char **init_array(void);
int loaded_client(void);

// connexion.c
int connection(my_server_t *server, client_t *client);

// my_select.c
int select_client(int activity, my_server_t *server, client_t *client);

//tools.c
char *recup_str(char *msg, char *type);
void send_to_client(client_t *client, int code, char *msg);
void sigint_handler( __attribute__((unused)) int sig_num);
int my_message_server(char *message, int return_value);
char *get_first_line(char *path);

//do_basics.c
void do_basics(client_t *client, char *command, int nb_command,
client_t *list_client);
void help_logout_users(client_t *client, int command, client_t *list_client);
void login_user_message_subscrie_unsubscribe(client_t *client, int size,
char *command, client_t *list_client);
void send_message(client_t *client, int size, char *command,
client_t *list_client);

//redir_command.c
void redir_in_command(client_t *client, char *command, int nb_command,
client_t *list_client);

//display_help.c
void display_help(client_t *client);

//display_users.c
void display_users(client_t *client, client_t *list_client);

//logout_client.c
void logout_client(client_t *client, client_t *list_client);

//send_error_to_client.c
void send_error_to_client(client_t *client, int nb, char *message);

//get_info_user.c
void get_info_user(client_t *client, client_t *list_client, char *command);

//display_messages.c
void display_messages(client_t *client, char *command);

//free_array.c
void free_array(char **array);

//subscribe.c
void subscribe(client_t *client, char *command);

//clean_str.c
char *clean_str(char *str);

//check_user.c
int check_account(client_t *client, client_t *list_client);

//unsubscribe.c
void unsubscribe(client_t *client, char *command);
char *delete_account(char *login, char *str);
int check_errors_unsubscribe(void *folder, client_t *client);
void unsubscribe_in_team(client_t *client, char *path, struct stat s);
void unsubscribe_log(client_t *client);

//send_message.c
void send_message_to_client_with_argument(client_t *client, int code,
char *message, char *str);
char *my_concat(char *src, char *dest);
char *conc_mess(char *path, char *str_1, char *str_2);
void send_without_log_history(char **array, client_t *client,
client_t *list_client);

//send_message_to_user.c
void send_message_to_user(client_t *client, char *command,
client_t *list_client);

//is_good_argument.c
int is_good_argument(char **array, int loop);

//str_without_quotes.c
char *str_without_quotes(char *str);

//command_to_array.c
char **command_to_array(char *str, client_t *client);

//info.c
void info_command(client_t *client, char *command, client_t *list_client);
void info_channel(client_t *client);
void info_team(client_t *client);
void info_thread(client_t *client);

//create.c
void create_command(client_t *client, char *command);
void create_team(client_t *client, char **array);
void create_channel(client_t *client, char **array);
void create_thread(client_t *client, char **array);
void reply_to_thread(client_t *client, char **array);
int write_in_file(client_t *client, char *path, char *name_team, char *message);
int create_acces_file(char *path_folder);
char *my_concat_path(char *path, char c, char *file);
int dir_threads_is_exist(DIR *dir, char *folder, client_t *client);

//list.c
void list_command(client_t *client, char *command);
void list_channels(client_t *client);
void list_threads(client_t *client);
void list_teams(client_t *client);
void list_replies(client_t *client);

//use.c
void use_command(client_t *client, char *command);
void free_and_unset_use(client_t *client);
void check_display_team_channel(int my_error, client_t *client);
void check_display_team_channel_thread(client_t *client,
char **array, int my_error);

// set_team_channel_thread.c
void set_team_channel_thread(client_t *client, char **array);
int search_thread_in_database(client_t *client, char *uuid_name);

// set_team_channel.c
void set_team_channel(client_t *client, char **array);
int search_channel_in_database(client_t *client, char *uuid_name);

//set_team.c
void set_team(client_t *client, char **array);
int search_team_in_database(client_t *client, char *uuid_name);

// unset_use.c
void unset_use(client_t *client);

//uuid.c
char *set_uuid_client(int fd);
char *create_uuid_client(char *name);
char *extract_uuid_client(char *path);
char *recup_uuid_client(char *name);

//get_last_line.c
char *get_last_line(char *path);


int log_server_event_channel_created(client_t *client, char *channel_name,
char *desc);

char *get_uuid_team_for_channel(client_t *client);
char *get_uuid_channel_for_log(client_t *client, char *name_channel);
int log_server_thread_created(client_t *client, char *name_thread,
char *message);


#endif /* !INCLUDE_H_ */