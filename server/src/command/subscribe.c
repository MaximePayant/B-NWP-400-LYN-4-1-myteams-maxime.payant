/*
** EPITECH PROJECT, 2021
** subscribe.c
** File description:
** subscribe.c
*/

#include <stdio.h>
#include <malloc.h>
#include "server.h"
#include "libs/myteams/logging_server.h"

void subscribe(server_t *server, client_t *client, const char *command)
{
    char *args = get_args(command);
    uuid_t team_uuid;
    char *client_uuid = malloc(sizeof(char) * 37);
    team_t *target = NULL;

    uuid_parse(args, team_uuid);
    target = get_team_by_uuid(&server->teams, team_uuid);
    if (!target) {
        dprintf(client->socket, "441 {%s}\r\n", team_uuid);
        return;
    }
    uuid_unparse(client->uuid, client_uuid);
    server_event_user_subscribed(args, client_uuid);
    add_uuid(&target->list_uuid, client->uuid, NULL);
    dprintf(client->socket, "108 Subscription done{%s}{%s}\r\n",
    client_uuid, args);
    free(client_uuid);
}