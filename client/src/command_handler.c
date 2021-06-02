/*
** EPITECH PROJECT, 2021
** command_handler.cpp
** File description:
** command_handler.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

static char *get_args(char *command)
{
    return (strstr(command, " "));
}

static char *get_code(char *command)
{
    return (strtok(command, " "));
}

static char *get_full_command(client_t *client)
{
    char *respond = "\0";
    char *complete = NULL;
    size_t size = 0;
    size_t mem = 0;

    do {
        getline(&respond, &size, client->file);
        mem = ((!complete) ? 0 : strlen(complete)) + strlen(respond);
        if (!complete)
            complete = strdup(respond);
        else {
            complete = realloc(complete, mem);
            strcat(complete, respond);
        }
    } while (!strstr(complete, "\r\n"));
    free(respond);
    return (complete);
}

int command_handler(client_t *client)
{
    char *args = NULL;
    char *code = NULL;
    char *complete = NULL;

    complete = get_full_command(client);
    code = strdup(complete);
    args = get_args(complete);
    code = get_code(code);
    code_handler(code, args);
    if (strcmp(code, "102") == 0)
        client->exit = 1;
    free(code);
    free(complete);
    return (0);
}