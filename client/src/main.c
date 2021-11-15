/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** main
*/

#include <string.h>
#include <stdio.h>
#include "include_client.h"

void help(void)
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\tip\tis the server ip address \
    on which the server socket listens\n");
    printf("\tport\tis the port number on which the server socket listens\n");
}

int main(int ac, char **av)
{
    int nb = 0;

    if (ac != 2 && ac != 3)
        return 84;
    if (strcmp(av[1], "-h") == 0 && ac == 2)
        help();
    else if (ac == 3) {
        nb = my_client(av[1], av[2]);
        printf("Client Exit...\n");
        return nb;
    }
    else
        return 84;
    return 0;
}