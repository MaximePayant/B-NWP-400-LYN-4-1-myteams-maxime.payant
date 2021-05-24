/*
** EPITECH PROJECT, 2021
** logout.c
** File description:
** logout.c
*/

#include <stdio.h>
#include <malloc.h>
#include "server.h"
#include "libs/myteams/logging_server.h"

void logout(server_t *server, client_t *client, const char *command)
{
    char *user_uuid = malloc(sizeof(char) * 37);

    (void) command;
    uuid_unparse(client->uuid, user_uuid);
    server_event_user_logged_out(user_uuid);
    dprintf(client->socket, "102 Disconnection successfully{%s}{%s}\r\n",
            "UUID", "NAME");
    delete_client(server, client->socket);
    free(user_uuid);
}