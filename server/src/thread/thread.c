/*
** EPITECH PROJECT, 2021
** thread.c
** File description:
** thread.c
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "list_uuid.h"

void delete_team(server_t *server, uuid_t target_uuid)
{
    team_t *current = server->teams;
    team_t *delete = NULL;

    while (current) {
        if (uuid_compare(current->uuid, target_uuid) == 0)
            delete = current;
        current = current->next;
    }
    if (!delete)
        return;
    current = delete->next;
    uuid_clear(delete->uuid);
    free(delete->name);
    free(delete->description);
    if (current)
        current->prev = delete->prev;
    if (!delete->prev)
        server->teams = delete->next;
    else
        delete->prev->next = delete->next;
    free(delete);
}

team_t *get_team_by_uuid(team_t **first, uuid_t target_uuid)
{
    team_t *current = *first;

    while (current && uuid_compare(current->uuid, target_uuid) != 0)
        current = current->next;
    return (current);
}

team_t *get_team_by_name(team_t **first, char *name)
{
    team_t *current = *first;

    while (current && strcmp(name, current->name) != 0)
        current = current->next;
    return (current);
}

void add_user_team(team_t **first, uuid_t team_uuid, client_t *client)
{
    team_t *target_team = get_team_by_uuid(first, team_uuid);

    if (!target_team)
        return;
    create_uuid(&target_team->list_uuid, client->uuid, NULL);
}

void remove_user_team(team_t **first, uuid_t team_uuid, client_t *client)
{
    team_t *target_team = get_team_by_uuid(first, team_uuid);

    if (!target_team)
        return;
    delete_uuid(&target_team->list_uuid, client->uuid);
}