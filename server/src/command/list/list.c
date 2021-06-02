/*
** EPITECH PROJECT, 2021
** list.cpp
** File description:
** list.cpp
*/

#include <stdio.h>
#include <malloc.h>
#include "server.h"

static void check_thread(server_t *server, client_t *client, char *tmp_uuid)
{
    channel_t *channel = NULL;
    team_t *team = NULL;

    if (!uuid_is_null(client->team_uuid) && !uuid_is_null(client->channel_uuid)
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
                display_list_threads(server, client);
        }
    }
}

static void check_message_part2(server_t *server, client_t *client,
team_t *team, char *tmp_uuid)
{
    channel_t *channel = NULL;

    channel = get_channel_by_uuid(&team->channels,
    client->channel_uuid);
    if (!channel) {
        uuid_unparse(client->channel_uuid, tmp_uuid);
        dprintf(client->socket, "442 {%s}\r\n", tmp_uuid);
    } else if (!get_thread_by_uuid(&channel->threads,
    client->thread_uuid)) {
        uuid_unparse(client->thread_uuid, tmp_uuid);
        dprintf(client->socket, "443 {%s}\r\n", tmp_uuid);
    } else
        display_list_messages(server, client);
}

static void check_message(server_t *server, client_t *client, char *tmp_uuid)
{
    team_t *team = NULL;

    if (!uuid_is_null(client->team_uuid) && !uuid_is_null(client->channel_uuid)
        && !uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        if (!team) {
            uuid_unparse(client->team_uuid, tmp_uuid);
            dprintf(client->socket, "441 {%s}\r\n", tmp_uuid);
        } else
            check_message_part2(server, client, team, tmp_uuid);
    }
}

static void check_channel(server_t *server, client_t *client, char *tmp_uuid)
{
    team_t *team = NULL;

    if (!uuid_is_null(client->team_uuid) && uuid_is_null(client->channel_uuid)
             && uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        if (!team) {
            uuid_unparse(client->team_uuid, tmp_uuid);
            dprintf(client->socket, "441 {%s}\r\n", tmp_uuid);
        } else
            display_list_channels(server, client);
    }
}

void list(server_t *server, client_t *client, const char *command)
{
    char *tmp_uuid = malloc(sizeof(char) * 37);

    (void)command;
    if (uuid_is_null(client->team_uuid) && uuid_is_null(client->channel_uuid)
    && uuid_is_null(client->thread_uuid)) {
        display_list_teams(server, client);
        return;
    }
    check_channel(server, client, tmp_uuid);
    check_thread(server, client, tmp_uuid);
    check_message(server, client, tmp_uuid);
    dprintf(client->socket, "412 Nothing to show\r\n");
    free(tmp_uuid);
}