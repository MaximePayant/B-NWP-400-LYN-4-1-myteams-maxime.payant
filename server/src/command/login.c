/*
** EPITECH PROJECT, 2021
** login.c
** File description:
** login.c
*/

#include <stdio.h>
#include "server.h"

void login(server_t *server, client_t *client, const char *command)
{
    (void) server;
    (void) command;
    dprintf(client->socket, "101 Connection Successful{%s}{%s}\r\n",
    "UUID", "NAME");
}
