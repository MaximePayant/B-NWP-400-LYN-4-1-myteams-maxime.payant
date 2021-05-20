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

int command_handler(client_t *client, char *command)
{
    FILE *file = fdopen(client->socket, "rw");
    char *respond = "\0";
    size_t size = 0;
    char *complete = malloc(sizeof(char));

    complete[0] = '\0';
    send_command(client, command);
    while (!strstr(complete, "\r\n")) {
        getline(&respond, &size, file);
        complete = realloc(complete, strlen(complete) + strlen(respond));
        strcat(complete, respond);
    }
    printf("%s", complete);
    free(respond);
    free(complete);
    free(file);
    return (0);
}