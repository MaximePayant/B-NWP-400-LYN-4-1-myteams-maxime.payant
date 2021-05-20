/*
** EPITECH PROJECT, 2021
** Delivery
** File description:
** message
*/


#include <stdio.h>
#include "server.h"

void message(server_t *server, client_t *client, const char *command)
{
    (void) server;
    (void) command;
    dprintf(client->socket, "YAPADEMESSAGE\r\n");
}