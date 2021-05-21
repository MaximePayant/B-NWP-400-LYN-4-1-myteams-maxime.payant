/*
** EPITECH PROJECT, 2021
** create.cpp
** File description:
** create.cpp
*/

#include <string.h>
#include <malloc.h>
#include "server.h"
#include "channels.h"

void create(server_t *server, client_t *client, const char *command)
{
    char *new_command = strdup(command);
    char *name = NULL;
    char *description = NULL;

    strtok(new_command, " ");
    name = strtok(NULL, " ");
    description = strtok(NULL, " ");
    if (!name || !description)
        return;
    if (uuid_is_null(client->team_uuid) && uuid_is_null(client->channel_uuid)
    && uuid_is_null(client->thread_uuid))
        create_team(server, client, name, description);
    if (!uuid_is_null(client->team_uuid) && uuid_is_null(client->channel_uuid)
        && uuid_is_null(client->thread_uuid))
        create_channel(
        &get_team_by_uuid(&server->teams, client->team_uuid)->channels, client,
        name, description);
    free(new_command);
}