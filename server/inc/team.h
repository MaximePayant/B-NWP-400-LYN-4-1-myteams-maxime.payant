/*
** EPITECH PROJECT, 2021
** team.h
** File description:
** team.h
*/

#ifndef TEAM
#define TEAM

#include <uuid/uuid.h>
#include "list_uuid.h"

typedef struct team_s {
    uuid_t uuid;
    char *name;
    char *description;
} team_t;

#endif //TEAM
