/*
** EPITECH PROJECT, 2021
** help.cpp
** File description:
** help.cpp
*/

#include <stdio.h>
#include "server.h"

void help(server_t *server, client_t *client, const char *command)
{
    (void) server;
    (void) command;
    dprintf(client->socket, "YAPADHELP\n");
}
