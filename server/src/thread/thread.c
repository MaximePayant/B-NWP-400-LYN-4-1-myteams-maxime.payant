/*
** EPITECH PROJECT, 2021
** thread.c
** File description:
** thread.c
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "threads.h"

void delete_thread(thread_t **first, uuid_t target_uuid)
{
    thread_t *current = *first;
    thread_t *delete = NULL;

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
    free(delete->message);
    if (current)
        current->prev = delete->prev;
    if (!delete->prev)
        *first = delete->next;
    else
        delete->prev->next = delete->next;
    free(delete);
}

thread_t *get_thread_by_uuid(thread_t **first, uuid_t target_uuid)
{
    thread_t *current = *first;

    while (current && uuid_compare(current->uuid, target_uuid) != 0)
        current = current->next;
    return (current);
}

thread_t *get_thread_by_name(thread_t **first, char *name)
{
    thread_t *current = *first;

    while (current && strcmp(name, current->name) != 0)
        current = current->next;
    return (current);
}