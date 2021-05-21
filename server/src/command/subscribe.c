/*
** EPITECH PROJECT, 2021
** subscribe.c
** File description:
** subscribe.c
*/

#include <stdio.h>
#include "server.h"

void subscribe(server_t *server, client_t *client, const char *command)
{
    char *ars = get_args(command);
    uuid_t uuid;
    team_t *target = NULL;

    uuid_parse(ars, uuid);
    target = get_team_by_uuid(&server->teams, uuid);
    if (!target) {
        dprintf(client->socket, "408 Subscription fail, team not found\r\n");
        return;
    }
    add_uuid(&target->list_uuid, client->uuid, NULL);
    dprintf(client->socket, "108 Subscription done\r\n");
}