/*
** EPITECH PROJECT, 2021
** subscribed.c
** File description:
** subscribed.c
*/

#include <stdio.h>
#include <malloc.h>
#include "server.h"

void subscribed(server_t *server, client_t *client, const char *command)
{
    char *args = get_args(command);
    uuid_t team_uuid;
    team_t *target = NULL;
    char *uuid_str = malloc(sizeof(char) * 37);

    if (args) {
        uuid_parse(args, team_uuid);
        target = get_team_by_uuid(&server->teams, team_uuid);
    }
    if (!target) {
        target = server->teams;
        dprintf(client->socket, "114 \n");
        while (target) {
            if (is_in_team(target, client->uuid)) {
                uuid_unparse(target->uuid, uuid_str);
                dprintf(client->socket, "{%s}{%s}{%s}\n", uuid_str, target->name, target->description);
            }
            target = target->next;
        }
        dprintf(client->socket, "\r\n");
    }
}