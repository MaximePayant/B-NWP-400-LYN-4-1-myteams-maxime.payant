/*
** EPITECH PROJECT, 2021
** Delivery
** File description:
** users
*/

#include <stdio.h>
#include "clients.h"
#include "server.h"

void users(server_t *server, client_t *client, const char *command)
{
    client_t *current = server->client;

    (void) command;
    dprintf(client->socket, "104 ");
    while (current) {
        dprintf(client->socket, "{%s}", current->uuid_str);
        dprintf(client->socket, "{%s}", current->user_name);
        dprintf(client->socket, "{%d}\n", current->connected);
        current = current->next;
    }
    dprintf(client->socket, "\r\n");
}