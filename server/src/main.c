/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** main
*/

#include <string.h>
#include <stdio.h>
#include "include.h"

void help(void)
{
    printf("USAGE: ./myteams_server port\n");
    printf("\tport\tis the port number on which the server socket listens.\n");
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    if (strcmp(av[1], "-h") == 0)
        help();
    else
        return my_server(av[1]);
    return 0;
}