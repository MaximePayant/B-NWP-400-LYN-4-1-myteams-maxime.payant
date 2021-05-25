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
    team_t *team = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;

    strtok(new_command, " ");
    name = strtok(NULL, " ");
    description = strtok(NULL, " ");
    if (!uuid_is_null(client->team_uuid) && !uuid_is_null(client->channel_uuid)
        && !uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        channel = get_channel_by_uuid(&team->channels, client->channel_uuid);
        thread = get_thread_by_uuid(&channel->threads, client->thread_uuid);
        print_new_reply(create_message(&thread->message, client, strstr(command, " ") + 1), client);
    }
    if (!name || !description)
        return;
    if (uuid_is_null(client->team_uuid) && uuid_is_null(client->channel_uuid)
    && uuid_is_null(client->thread_uuid)) {
        create_team(server, client, name, description);
        return;
    }
    if (!uuid_is_null(client->team_uuid) && uuid_is_null(client->channel_uuid)
        && uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        create_channel(&team->channels, client, name, description);
        return;
    }
    if (!uuid_is_null(client->team_uuid) && !uuid_is_null(client->channel_uuid)
        && uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        channel = get_channel_by_uuid(&team->channels, client->channel_uuid);
        create_thread(&channel->threads, client, name, description);
        return;
    }
    free(new_command);
}