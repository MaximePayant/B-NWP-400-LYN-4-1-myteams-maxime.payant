/*
** EPITECH PROJECT, 2021
** command_handler.cpp
** File description:
** command_handler.cpp
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

int send_command(client_t *client, char *command)
{
    FILE *file = fdopen(client->socket, "rw");
    char *respond = "\0";
    size_t size = 0;

    dprintf(client->socket, "%s\n", command);
    while (!strstr(respond, "\r\n")) {
        getline(&respond, &size, file);
        printf("%s", respond);
    }
    free(respond);
    free(file);
    return (0);
}