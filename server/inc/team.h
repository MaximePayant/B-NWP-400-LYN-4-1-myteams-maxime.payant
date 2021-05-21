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
    list_uuid *list_uuid;
    struct team_s *next;
    struct team_s *prev;
} team_t;

team_t *create_team(server_t *server, client_t *client,
char *name, char *description);
team_t *get_team_by_uuid(team_t **first, uuid_t target_uuid);
team_t *get_team_by_name(team_t **first, char *name);
int is_in_team(team_t *team, uuid_t uuid);

#endif //TEAM
