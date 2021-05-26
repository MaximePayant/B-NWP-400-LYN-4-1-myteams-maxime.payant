/*
** EPITECH PROJECT, 2021
** logout.c
** File description:
** logout.c
*/

#include <stdio.h>
#include "clients.h"
#include <malloc.h>
#include "server.h"
#include "libs/myteams/logging_server.h"

void logout(server_t *server, client_t *client, const char *command)
{
    (void) command;

    if (client->connected) {
        client->connected = 0;
        server_event_user_logged_out(client->uuid_str);
        dprintf(client->socket, "102 Disconnection successfully{%s}{%s}\r\n",
        client->uuid_str, client->user_name);
        delete_client(server, client->socket);
        return;
    }
}