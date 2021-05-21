/*
** EPITECH PROJECT, 2021
** logout.c
** File description:
** logout.c
*/

#include <stdio.h>
#include "server.h"

void logout(server_t *server, client_t *client, const char *command)
{
    (void) command;
    dprintf(client->socket, "102 Disconnection successfully\r\n");
    delete_client(server, client->socket);
}