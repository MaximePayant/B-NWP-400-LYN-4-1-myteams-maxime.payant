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

static void create_new_resources(server_t *server,
client_t *client, char **args)
{
    team_t *team = NULL;
    channel_t *channel = NULL;

    if (uuid_is_null(client->team_uuid) && uuid_is_null(client->channel_uuid)
        && uuid_is_null(client->thread_uuid))
        create_team(server, client, args[0], args[1]);
    else if (!uuid_is_null(client->team_uuid) &&
             uuid_is_null(client->channel_uuid)
             && uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        if (!team)
            dprintf(client->socket, "441 {%s}\r\n", client->team_uuid);
        else
            create_channel(&team->channels, client, args[0], args[1]);
    } else if (!uuid_is_null(client->team_uuid) &&
               !uuid_is_null(client->channel_uuid)
               && uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        if (!team)
            dprintf(client->socket, "441 {%s}\r\n", client->team_uuid);
        else {
            channel = get_channel_by_uuid(&team->channels,
                                          client->channel_uuid);
            if (!channel)
                dprintf(client->socket, "442 {%s}\r\n", client->channel_uuid);
            else
                create_thread(&channel->threads, client, args[0], args[1]);
        }
    }
}

void create(server_t *server, client_t *client, const char *command)
{
    char **args = get_params(command);
    team_t *team = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;

    if (!uuid_is_null(client->team_uuid) && !uuid_is_null(client->channel_uuid)
        && !uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        channel = get_channel_by_uuid(&team->channels, client->channel_uuid);
        thread = get_thread_by_uuid(&channel->threads, client->thread_uuid);
        print_new_reply(create_message(&thread->message, client,
        strstr(command, " ") + 1), client);
    }
    if (!args[0] || !args[1])
        return;
    create_new_resources(server, client, args);
}