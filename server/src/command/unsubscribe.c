/*
** EPITECH PROJECT, 2021
** unsubscribe.c
** File description:
** unsubscribe.c
*/

#include <stdio.h>
#include "server.h"

void unsubscribe(server_t *server, client_t *client, const char *command)
{
    char *ars = get_args(command);
    uuid_t uuid;
    team_t *target = NULL;

    uuid_parse(ars, uuid);
    target = get_team_by_uuid(&server->teams, uuid);
    if (!target) {
        dprintf(client->socket, "409 Unsubscription fail, team not found\r\n");
        return;
    }
    if (!is_in_team(target, client->uuid)) {
        dprintf(client->socket, "409 Unsubscription fail,"
        " you're not in the team\r\n");
        return;
    }
    delete_uuid(&target->list_uuid, client->uuid);
    dprintf(client->socket, "109 Unsubscription done\r\n");
}