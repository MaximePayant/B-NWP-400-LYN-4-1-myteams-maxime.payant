/*
** EPITECH PROJECT, 2021
** command_handler.cpp
** File description:
** command_handler.cpp
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "client.h"

int send_command(client_t *client, char *command)
{
    FILE *file = fdopen(client->socket, "rw");
    char *respond = NULL;
    size_t size = 0;

    dprintf(client->socket, "%s\n", command);
    getline(&respond, &size, file);
    puts(respond);
    free(respond);
    return (0);
}