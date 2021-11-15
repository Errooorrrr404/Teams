/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** get_last_line
*/

#include "include.h"

char *get_first_line(char *path)
{
    FILE *fp;
    char *line;
    size_t len = 0;

    fp = fopen(path, "r");
    if (fp == NULL)
        return NULL;
    line = NULL;
    getline(&line, &len, fp);
    fclose(fp);
    return line;
}

char *get_last_line(char *path)
{
    FILE *fp;
    char *line;
    size_t len = 0;
    ssize_t read;

    fp = fopen(path, "r");
    if (fp == NULL)
        return NULL;
    line = NULL;
    read = getline(&line, &len, fp);
    while (read != -1) {
        read = getline(&line, &len, fp);
    }
    fclose(fp);
    return line;
}