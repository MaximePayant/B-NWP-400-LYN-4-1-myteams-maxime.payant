/*
** EPITECH PROJECT, 2021
** thread_create.c
** File description:
** thread_create.c
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "list_uuid.h"
#include "libs/myteams/logging_server.h"

static void define_value(team_t *new_team, char *name, char *description)
{
    int last = strlen(description) - 1;

    new_team->next = NULL;
    new_team->prev = NULL;
    new_team->list_uuid = NULL;
    new_team->channels = NULL;
    uuid_generate(new_team->uuid);
    new_team->name = strdup(name);
    description[last] = (description[last] == '\n') ? '\0' : description[last];
    new_team->description = strdup(description);
    new_team->uuid_str = malloc(sizeof(char) * 37);
    uuid_unparse(new_team->uuid, new_team->uuid_str);
}

static void send_event(server_t *server, char *team_uuid, char *name,
char *description)
{
    client_t *current = server->client;

    while (current) {
        if (!current->connected) {
            current = current->next;
            continue;
        }
        dprintf(current->socket, "222 New team created{team}{%s}{%s}{%s}\r\n",
        team_uuid, name, description);
        current = current->next;
    }
}

team_t *create_team(server_t *server, client_t *client,
char *name, char *description)
{
    team_t *new_team = malloc(sizeof(team_t));
    team_t *current = server->teams;

    if (get_team_by_name(&server->teams, name)) {
        dprintf(client->socket, "439 \r\n");
        return (NULL);
    }
    if (strlen(name) > MAX_NAME_LENGTH) {
        dprintf(client->socket, "411 Team's name too long\r\n");
        return (NULL);
    }
    if (strlen(description) > MAX_DESCRIPTION_LENGTH) {
        dprintf(client->socket, "411 Team's description too long\r\n");
        return (NULL);
    }
    define_value(new_team, name, description);
    if (!current)
        server->teams = new_team;
    else {
        while (current->next)
            current = current->next;
        current->next = new_team;
        new_team->prev = current;
    }
    server_event_team_created(new_team->uuid_str, new_team->name, client->uuid_str);
    dprintf(client->socket, "111 Team successfully created{team}{%s}{%s}{%s}\r\n", new_team->uuid_str, name, description);
    send_event(server, new_team->uuid_str, name, description);
    return (new_team);
}