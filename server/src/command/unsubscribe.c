/*
** EPITECH PROJECT, 2021
** unsubscribe.c
** File description:
** unsubscribe.c
*/

#include <stdio.h>
#include <malloc.h>
#include "server.h"
#include "libs/myteams/logging_server.h"

void unsubscribe(server_t *server, client_t *client, const char *command)
{
    char *args = get_args(command);
    uuid_t uuid;
    char *client_uuid = malloc(sizeof(char) * 37);
    team_t *target = NULL;

    uuid_parse(args, uuid);
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
    uuid_unparse(client->uuid, client_uuid);
    server_event_user_unsubscribed(args, client_uuid);
    delete_uuid(&target->list_uuid, client->uuid);
    dprintf(client->socket, "109 Unsubscription done\r\n");
    free(client_uuid);
}