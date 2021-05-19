/*
** EPITECH PROJECT, 2021
** info.c
** File description:
** info.c
*/

#include <stdio.h>
#include <malloc.h>
#include "server.h"

static void display_teams(server_t *server, client_t *client)
{
    team_t *current = server->teams;
    int i = 0;
    char *uuid = malloc(sizeof(char) * 37);

    while (current) {
        uuid_unparse(current->uuid, uuid);
        dprintf(client->socket, "Team n°%d:\n", i);
        dprintf(client->socket, "\tName: %s\n", current->name);
        dprintf(client->socket, "\tUuid: %s\n", uuid);
        dprintf(client->socket, "\tDescription: %s\n", current->description);
        dprintf(client->socket, "\tChannels: BAH YA PA FRR");
        current = current->next;
        if (current)
            i++;
    }
    dprintf(client->socket, "\r\n");
    free(uuid);
}

void info(server_t *server, client_t *client, const char *command)
{
    (void)command;
    if (!uuid_is_null(client->team_uuid)) {
        display_teams(server, client);
        return;
    }
    dprintf(client->socket, "BA YA R CHEH\r\n");
}