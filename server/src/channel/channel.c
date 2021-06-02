/*
** EPITECH PROJECT, 2021
** thread.c
** File description:
** thread.c
*/

#include <string.h>
#include "server.h"
#include "channels.h"

void delete_channel(channel_t **first, uuid_t target_uuid)
{
    channel_t *current = *first;
    channel_t *delete = NULL;

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
        *first = delete->next;
    else
        delete->prev->next = delete->next;
    free(delete);
}

channel_t *get_channel_by_uuid(channel_t **first, uuid_t target_uuid)
{
    channel_t *current = *first;

    while (current && uuid_compare(current->uuid, target_uuid) != 0)
        current = current->next;
    return (current);
}

channel_t *get_channel_by_name(channel_t **first, char *name)
{
    channel_t *current = *first;

    while (current && strcmp(name, current->name) != 0)
        current = current->next;
    return (current);
}