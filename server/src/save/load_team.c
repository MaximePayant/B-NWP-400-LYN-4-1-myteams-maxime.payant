/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** load_team.c
*/

#include <stdlib.h>
#include <string.h>

#include "libs/json_parser/json_parser.h"
#include "server.h"

static void load_subscriber(team_t *team, jsnp_value_t *value)
{
    list_uuid *uuid = malloc(sizeof(list_uuid));
    list_uuid *current = team->list_uuid;

    uuid->next = NULL;
    uuid->prev = NULL;
    uuid->string = strdup(value->str);
    uuid_parse(uuid->string, uuid->uuid);
    if (!current)
        team->list_uuid = uuid;
    else {
        while (current->next)
            current = current->next;
        current->next = uuid;
        uuid->prev = current;
    }
}

void load_team(server_t *server, jsnp_value_t *value)
{
    team_t *team = malloc(sizeof(team_t));
    team_t *current = server->teams;

    team->name = strdup(get_token(value, "Name")->value->str);
    team->description = strdup(get_token(value, "Description")->value->str);
    uuid_parse(get_token(value, "uuid")->value->str, team->uuid);
    team->channels = NULL;
    team->list_uuid = NULL;
    for (jsnp_value_t *it =
    get_token(value, "Subscribers")->value->array.lh_first;
    it; it = it->next.le_next)
        load_subscriber(team, it);

    int ctr = 1;
    for (jsnp_value_t *it =
    get_token(value, "Channels")->value->array.lh_first;
    it; it = it->next.le_next)
        load_channel(team, it);
    team->next = NULL;
    team->prev = NULL;
    if (!current)
        server->teams = team;
    else {
        while (current->next)
            current = current->next;
        current->next = team;
        team->prev = current;
    }
}