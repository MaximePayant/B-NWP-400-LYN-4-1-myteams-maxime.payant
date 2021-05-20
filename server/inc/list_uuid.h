/*
** EPITECH PROJECT, 2021
** uuid.h
** File description:
** uuid.h
*/

#ifndef UUID
#define UUID

#include <uuid/uuid.h>

typedef struct list_uuid_s
{
    uuid_t uuid;
    char *string;
    struct list_uuid_s *next;
    struct list_uuid_s *prev;
} list_uuid;

list_uuid *create_uuid(list_uuid **first, const uuid_t new_uuid, char *string);
list_uuid *search_uuid(list_uuid **first, const uuid_t target_uuid);
int delete_uuid(list_uuid **first, const uuid_t target_uuid);

#endif //UUID
