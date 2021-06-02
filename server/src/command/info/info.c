/*
** EPITECH PROJECT, 2021
** info.c
** File description:
** info.c
*/

#include <stdio.h>
#include <malloc.h>
#include "server.h"

static void check_thread_part2(server_t *server, client_t *client, team_t *team,
char *tmp_uuid)
{
    channel_t *channel = NULL;

    channel = get_channel_by_uuid(&team->channels
    ,client->channel_uuid);
    if (!channel) {
        uuid_unparse(client->channel_uuid, tmp_uuid);
        dprintf(client->socket, "442 {%s}", tmp_uuid);
    } else if (!get_thread_by_uuid(&channel->threads,
    client->thread_uuid)) {
        uuid_unparse(client->thread_uuid, tmp_uuid);
        dprintf(client->socket, "443 {%s}", tmp_uuid);
    } else
        display_info_thread(server, client);
}

static void check_thread(server_t *server, client_t *client, char *tmp_uuid)
{
    team_t *team = NULL;

    if (!uuid_is_null(client->team_uuid) && !uuid_is_null(client->channel_uuid)
             && !uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        if (!team) {
            uuid_unparse(client->team_uuid, tmp_uuid);
            dprintf(client->socket, "441 {%s}", tmp_uuid);
        } else
            check_thread_part2(server, client, team, tmp_uuid);
        return;
    }
}

static void check_channel(server_t *server, client_t *client, char *tmp_uuid)
{
    team_t *team = NULL;

    if (!uuid_is_null(client->team_uuid) && !uuid_is_null(client->channel_uuid)
             && uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        if (!team) {
            uuid_unparse(client->team_uuid, tmp_uuid);
            dprintf(client->socket, "441 {%s}", tmp_uuid);
        } else if (!get_channel_by_uuid(&team->channels,
        client->channel_uuid)) {
            uuid_unparse(client->channel_uuid, tmp_uuid);
            dprintf(client->socket, "442 {%s}", tmp_uuid);
        } else
            display_info_channel(server, client);
        return;
    }
}

void info(server_t *server, client_t *client, const char *command)
{
    char *tmp_uuid = malloc(sizeof(char) * 37);

    (void)command;
    if (!uuid_is_null(client->team_uuid) && uuid_is_null(client->channel_uuid)
    && uuid_is_null(client->thread_uuid)) {
        if (!get_team_by_uuid(&server->teams, client->team_uuid)) {
            uuid_unparse(client->team_uuid, tmp_uuid);
            dprintf(client->socket, "441 {%s}", tmp_uuid);
        } else
            display_info_teams(server, client);
        return;
    }
    check_channel(server, client, tmp_uuid);
    check_thread(server, client, tmp_uuid);
    dprintf(client->socket, "413 Nothing to show\r\n");
}