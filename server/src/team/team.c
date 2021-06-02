/*
** EPITECH PROJECT, 2021
** thread.c
** File description:
** thread.c
*/

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

int is_in_team(team_t *team, uuid_t uuid)
{
    list_uuid *current = team->list_uuid;

    while (current) {
        if (uuid_compare(uuid, current->uuid) == 0)
            return (1);
        current = current->next;
    }
    return (0);
}