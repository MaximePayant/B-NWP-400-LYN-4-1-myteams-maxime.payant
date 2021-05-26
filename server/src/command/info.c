/*
** EPITECH PROJECT, 2021
** info.c
** File description:
** info.c
*/

#include <stdio.h>
#include <malloc.h>
#include "server.h"

static void display_teams(server_t *server, client_t *client)
{
    char *uuid = malloc(sizeof(char) * 37);
    team_t *target = get_team_by_uuid(&server->teams, client->team_uuid);

    dprintf(client->socket, "113 ");
    uuid_unparse(target->uuid, uuid);
    dprintf(client->socket, "{team}\n");
    dprintf(client->socket, "{%s}", uuid);
    dprintf(client->socket, "{%s}", target->name);
    dprintf(client->socket, "{%s}", target->description);
    dprintf(client->socket, "\r\n");
    free(uuid);
}

static void display_channel(server_t *server, client_t *client)
{
    char *uuid = malloc(sizeof(char) * 37);
    team_t *team = get_team_by_uuid(&server->teams, client->team_uuid);
    channel_t *target = get_channel_by_uuid(&team->channels, client->channel_uuid);

    dprintf(client->socket, "113 ");
    uuid_unparse(target->uuid, uuid);
    dprintf(client->socket, "{channel}");
    dprintf(client->socket, "{%s}", uuid);
    dprintf(client->socket, "{%s}", target->name);
    dprintf(client->socket, "{%s}", target->description);
    dprintf(client->socket, "\r\n");
    free(uuid);
}

static void display_thread(server_t *server, client_t *client)
{
    char *uuid = malloc(sizeof(char) * 37);
    char *client_uuid = malloc(sizeof(char) * 37);
    team_t *team = get_team_by_uuid(&server->teams, client->team_uuid);
    channel_t *channel = get_channel_by_uuid(&team->channels, client->channel_uuid);
    thread_t *target = get_thread_by_uuid(&channel->threads, client->thread_uuid);

    dprintf(client->socket, "113 ");
    uuid_unparse(target->uuid, uuid);
    uuid_unparse(client->uuid, client_uuid);
    dprintf(client->socket, "{thread}");
    dprintf(client->socket, "{%s}", uuid);
    dprintf(client->socket, "{%s}", client_uuid);
    dprintf(client->socket, "{%s}", "TEAM");
    dprintf(client->socket, "{%s}", target->name);
    dprintf(client->socket, "{%s}", target->message->core);
    dprintf(client->socket, "\r\n");
    free(uuid);
    free(client_uuid);
}

void info(server_t *server, client_t *client, const char *command)
{
    char *tmp_uuid = malloc(sizeof(char) * 37);
    team_t *team = NULL;
    channel_t *channel = NULL;

    (void)command;
    if (!uuid_is_null(client->team_uuid) && uuid_is_null(client->channel_uuid)
    && uuid_is_null(client->thread_uuid)) {
        if (!get_team_by_uuid(&server->teams, client->team_uuid)) {
            uuid_unparse(client->team_uuid, tmp_uuid);
            dprintf(client->socket, "441 {%s}", tmp_uuid);
        } else
            display_teams(server, client);
        return;
    }
    else if (!uuid_is_null(client->team_uuid) && !uuid_is_null(client->channel_uuid)
    && uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        if (!team) {
            uuid_unparse(client->team_uuid, tmp_uuid);
            dprintf(client->socket, "441 {%s}", tmp_uuid);
        } else if (!get_channel_by_uuid(&team->channels, client->channel_uuid)) {
            uuid_unparse(client->channel_uuid, tmp_uuid);
            dprintf(client->socket, "442 {%s}", tmp_uuid);
        } else
            display_channel(server, client);
        return;
    }
    else if (!uuid_is_null(client->team_uuid) && !uuid_is_null(client->channel_uuid)
    && !uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        if (!team) {
            uuid_unparse(client->team_uuid, tmp_uuid);
            dprintf(client->socket, "441 {%s}", tmp_uuid);
        } else {
            channel = get_channel_by_uuid(&team->channels, client->channel_uuid);
            if (!channel) {
                uuid_unparse(client->channel_uuid, tmp_uuid);
                dprintf(client->socket, "442 {%s}", tmp_uuid);
            } else if (!get_thread_by_uuid(&channel->threads, client->thread_uuid)) {
                uuid_unparse(client->thread_uuid, tmp_uuid);
                dprintf(client->socket, "443 {%s}", tmp_uuid);
            } else
                display_thread(server, client);
        }
        return;
    }
    dprintf(client->socket, "413 Nothing to show\r\n");
}