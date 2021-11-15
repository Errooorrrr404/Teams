/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** str_to_word_array
*/

#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "include.h"
#include "struct_server.h"

char *transform_str(char *str)
{
    int have_flag = 0;
    int i = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] == '\"' && have_flag == 0) {
            str[i] = '#';
            have_flag = 1;
        } else if (str[i] == '\"' && have_flag == 1) {
            str[i] = ' ';
            have_flag = 0;
        }
    }
    str[i] = '\0';
    if (have_flag == 1)
        return NULL;
    return str;
}

char **command_to_array(char *str, client_t *client)
{
    str = transform_str(str);
    if (!str) {
        send_error_to_client(client, 500, "Error \" missing.");
        return NULL;
    }
    return (str_to_array(str, '#'));
}
