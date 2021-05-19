/*
** EPITECH PROJECT, 2021
** thread_create.c
** File description:
** thread_create.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "list_uuid.h"
#include "libs/myteams/logging_server.h"

void define_value(team_t *new_team, char *name, char *description)
{
    int last = strlen(description) - 1;

    new_team->next = NULL;
    new_team->prev = NULL;
    new_team->list_uuid = NULL;
    uuid_generate(new_team->uuid);
    new_team->name = strdup(name);
    description[last] = (description[last] == '\n') ? '\0' : description[last];
    new_team->description = strdup(description);
}

static void free_mem(char *str1, char *str2)
{
    free(str1);
    free(str2);
}

team_t *create_team(server_t *server, client_t *client,
char *name, char *description)
{
    team_t *new_team = malloc(sizeof(team_t));
    team_t *current = server->teams;
    char *teams_uuid = malloc(sizeof(char) * 37);
    char *client_uuid = malloc(sizeof(char) * 37);

    if (strlen(name) > MAX_NAME_LENGTH) {
        free_mem(teams_uuid, client_uuid);
        return (NULL);
    }
    if (strlen(description) > MAX_DESCRIPTION_LENGTH) {
        free_mem(teams_uuid, client_uuid);
        return (NULL);
    }
    define_value(new_team, name, description);
    uuid_unparse(new_team->uuid, teams_uuid);
    uuid_unparse(client->uuid, client_uuid);
    if (!current)
        server->teams = new_team;
    else {
        while (current->next)
            current = current->next;
        current->next = new_team;
        new_team->prev = current;
    }
    server_event_team_created(teams_uuid, new_team->name, client_uuid);
    free_mem(teams_uuid, client_uuid);
    dprintf(client->socket,
            "Thread successfully created\r\n");
    return (new_team);
}