/*
** EPITECH PROJECT, 2021
** list_uuid.c
** File description:
** list_uuid.c
*/

#include <malloc.h>
#include <string.h>
#include "list_uuid.h"

list_uuid *create_uuid(list_uuid **first, const uuid_t new_uuid, char *string)
{
    list_uuid *new_node = malloc(sizeof(list_uuid));
    list_uuid *current = *first;

    new_node->next = NULL;
    new_node->prev = NULL;
    uuid_copy(new_node->uuid, new_uuid);
    new_node->string = string;
    if (!current) {
        *first = new_node;
        return (new_node);
    }
    while (current->next)
        current = current->next;
    current->next = new_node;
    new_node->prev = current;
    return (new_node);
}

list_uuid *search_uuid(list_uuid **first, const uuid_t target_uuid)
{
    list_uuid *current = *first;

    while (current && uuid_compare(current->uuid, target_uuid) != 0)
        current = current->next;
    return ((current) ? current : NULL);
}

int delete_uuid(list_uuid **first, const uuid_t target_uuid)
{
    list_uuid *current = *first;
    list_uuid *delete = NULL;

    while (current && uuid_compare(current->uuid, target_uuid) != 0)
        current = current->next;
    if (!current)
        return (-1);
    delete = current;
    current = current->prev;
    if (current)
        current->next = delete->next;
    if (delete->next)
        delete->next->prev = delete->prev;
    uuid_clear(delete->uuid);
    free(delete->string);
    free(delete);
    return (0);
}