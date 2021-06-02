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

static void create_new_rsc_part2(server_t *server, client_t *client,
team_t *team, char **args)
{
    char *tmp_uuid = malloc(sizeof(char) * 37);
    channel_t *channel = NULL;

    if (!uuid_is_null(client->team_uuid)
        && !uuid_is_null(client->channel_uuid)
        && uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        if (!team) {
            uuid_unparse(client->team_uuid, tmp_uuid);
            dprintf(client->socket, "441 {%s}\r\n", tmp_uuid);
        } else {
            channel = get_channel_by_uuid(&team->channels,
            client->channel_uuid);
            if (!channel) {
                uuid_unparse(client->channel_uuid, tmp_uuid);
                dprintf(client->socket, "442 {%s}\r\n", tmp_uuid);
            } else
                create_thread(&channel->threads, client, args[0], args[1]);
        }
    }
    free(tmp_uuid);
}

static void create_new_resources(server_t *server,
client_t *client, char **args)
{
    char *tmp_uuid = malloc(sizeof(char) * 37);
    team_t *team = NULL;

    if (uuid_is_null(client->team_uuid) && uuid_is_null(client->channel_uuid)
    && uuid_is_null(client->thread_uuid))
        create_team(server, client, args[0], args[1]);
    else if (!uuid_is_null(client->team_uuid)
    && uuid_is_null(client->channel_uuid)
    && uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        if (!team) {
            uuid_unparse(client->team_uuid, tmp_uuid);
            dprintf(client->socket, "441 {%s}\r\n", tmp_uuid);
        } else
            create_channel(&team->channels, client, args[0], args[1]);
    }
    create_new_rsc_part2(server, client, team, args);
    free(tmp_uuid);
}

static void create_part2(client_t *client, team_t *team, const char *command,
char *tmp_uuid)
{
    channel_t *channel = NULL;
    thread_t *thread = NULL;

    channel = get_channel_by_uuid(&team->channels, client->channel_uuid);
    if (!channel) {
        uuid_unparse(client->channel_uuid, tmp_uuid);
        dprintf(client->socket, "442 {%s}\r\n", tmp_uuid);
    } else {
        thread = get_thread_by_uuid(&channel->threads, client->thread_uuid);
        if (!thread) {
            uuid_unparse(client->thread_uuid, tmp_uuid);
            dprintf(client->socket, "443 {%s}\r\n", tmp_uuid);
        } else
            print_new_reply(create_message(&thread->message, client,
            strstr(command, " ") + 1), client);
    }
}

void create(server_t *server, client_t *client, const char *command)
{
    char *tmp_uuid = malloc(sizeof(char) * 37);
    char **args = get_params(command);
    team_t *team = NULL;

    if (!uuid_is_null(client->team_uuid) && !uuid_is_null(client->channel_uuid)
    && !uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        if (!team) {
            uuid_unparse(client->team_uuid, tmp_uuid);
            dprintf(client->socket, "441 {%s}\r\n", tmp_uuid);
        } else
            create_part2(client, team, command, tmp_uuid);
    }
    if (!args[0] || !args[1])
        return;
    create_new_resources(server, client, args);
    free(tmp_uuid);
}