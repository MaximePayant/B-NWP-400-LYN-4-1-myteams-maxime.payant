/*
** EPITECH PROJECT, 2021
** subscribed.c
** File description:
** subscribed.c
*/

#include <stdio.h>
#include <malloc.h>
#include "server.h"

static void send_message_sub(team_t *target, client_t *client)
{
    if (is_in_team(target, client->uuid)) {
        dprintf(client->socket, "{%s}{%s}{%s}\n", client->uuid_str,
        target->name, target->description);
    }
}

void subscribed(server_t *server, client_t *client, const char *command)
{
    char *args = get_args(command);
    uuid_t team_uuid;
    team_t *target = NULL;

    if (args) {
        uuid_parse(args, team_uuid);
        target = get_team_by_uuid(&server->teams, team_uuid);
    }
    if (!target) {
        target = server->teams;
        dprintf(client->socket, "114 \n");
        while (target) {
            send_message_sub(target, client);
            target = target->next;
        }
        dprintf(client->socket, "\r\n");
    }
}