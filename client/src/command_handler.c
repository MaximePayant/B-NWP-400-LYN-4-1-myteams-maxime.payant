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

char *get_args(char *command)
{
    return (strstr(command, " "));
}

char *get_code(char *command)
{
    return (strtok(command, " "));
}

int command_handler(client_t *client, char *command)
{
    char *respond = "\0";
    size_t size = 0;
    char *complete = NULL;
    char *args = NULL;
    char *code = NULL;
    size_t mem = 0;

    send_command(client, command);
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
    code = strdup(complete);
    args = get_args(complete);
    code = get_code(code);
    code_handler(code, args);
    if (strcmp(code, "102") == 0)
        client->exit = 1;
    free(code);
    free(respond);
    free(complete);
    return (0);
}