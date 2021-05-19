/*
** EPITECH PROJECT, 2021
** list.cpp
** File description:
** list.cpp
*/

#include <stdio.h>
#include <malloc.h>
#include "server.h"

#include <string.h>

void display_teams(server_t *server, client_t *client)
{
    team_t *current = server->teams;
    int i = 0;
    char *uuid = malloc(sizeof(char) * 37);

    while (current) {
        uuid_unparse(current->uuid, uuid);
        dprintf(client->socket, "Team n°%d:\n", i);
        dprintf(client->socket, "\tName: %s\n", current->name);
        dprintf(client->socket, "\tUuid: %s\n", uuid);
        dprintf(client->socket, "\tDescription: %s", current->description);
        current = current->next;
        if (current)
            i++;
    }
    dprintf(client->socket, "\r\n");
    free(uuid);
}

void list(server_t *server, client_t *client, const char *command)
{
    (void)command;
    if (uuid_is_null(client->channel_uuid) && uuid_is_null(client->thread_uuid))
        display_teams(server, client);
}