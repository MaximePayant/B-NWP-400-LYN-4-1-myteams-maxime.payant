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
    char *uuid = malloc(sizeof(char) * 37);
    team_t *target = get_team_by_uuid(&server->teams, client->team_uuid);

    uuid_unparse(target->uuid, uuid);
    dprintf(client->socket, "Team %s(%s):\n", target->name, uuid);
    dprintf(client->socket, "\tName: %s\n", target->name);
    dprintf(client->socket, "\tUuid: %s\n", uuid);
    dprintf(client->socket, "\tDescription: %s\n", target->description);
    dprintf(client->socket, "\tChannels: BAH YA PA FRR");
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