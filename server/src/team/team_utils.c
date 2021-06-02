/*
** EPITECH PROJECT, 2021
** team_utils.cpp
** File description:
** team_utils.cpp
*/

#include "server.h"

void add_user_team(team_t **first, uuid_t team_uuid, client_t *client)
{
    team_t *target_team = get_team_by_uuid(first, team_uuid);

    if (!target_team)
        return;
    add_uuid(&target_team->list_uuid, client->uuid, NULL);
}

void remove_user_team(team_t **first, uuid_t team_uuid, client_t *client)
{
    team_t *target_team = get_team_by_uuid(first, team_uuid);

    if (!target_team)
        return;
    delete_uuid(&target_team->list_uuid, client->uuid);
}