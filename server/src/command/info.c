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
    char *channel_uuid = malloc(sizeof(char) * 37);
    team_t *target = get_team_by_uuid(&server->teams, client->team_uuid);
    channel_t *current = target->channels;

    dprintf(client->socket, "113 \n");
    uuid_unparse(target->uuid, uuid);
    dprintf(client->socket, "Team %s(%s):\n", target->name, uuid);
    dprintf(client->socket, "\tName: %s\n", target->name);
    dprintf(client->socket, "\tUuid: %s\n", uuid);
    dprintf(client->socket, "\tDescription: %s\n", target->description);
    dprintf(client->socket, "\tChannels: \n");
    while (current) {
        uuid_unparse(current->uuid, channel_uuid);
        dprintf(client->socket, "\t\tname: %s ", current->name);
        dprintf(client->socket, "uuid: %s", channel_uuid);
        if (current->next)
            dprintf(client->socket, "\n");
        current = current->next;
    }
    dprintf(client->socket, "\r\n");
    free(uuid);
}

static void display_channel(server_t *server, client_t *client)
{
    char *uuid = malloc(sizeof(char) * 37);
    team_t *team = get_team_by_uuid(&server->teams, client->team_uuid);
    channel_t *target = get_channel_by_uuid(&team->channels, client->channel_uuid);

    dprintf(client->socket, "113 \n");
    uuid_unparse(target->uuid, uuid);
    dprintf(client->socket, "Team %s(%s):\n", target->name, uuid);
    dprintf(client->socket, "\tName: %s\n", target->name);
    dprintf(client->socket, "\tUuid: %s\n", uuid);
    dprintf(client->socket, "\tDescription: %s\n", target->description);
    dprintf(client->socket, "\tthread: BAH YA PA FRR");
    dprintf(client->socket, "\r\n");
    free(uuid);
}

void info(server_t *server, client_t *client, const char *command)
{
    team_t *team = NULL;
    channel_t *channel = NULL;

    (void)command;
    if (!uuid_is_null(client->team_uuid) && uuid_is_null(client->channel_uuid)
    && uuid_is_null(client->thread_uuid)) {
        if (!get_team_by_uuid(&server->teams, client->team_uuid))
            dprintf(client->socket, "441 {%s}", client->team_uuid);
        else
            display_teams(server, client);
        return;
    }
    else if (!uuid_is_null(client->team_uuid) && !uuid_is_null(client->channel_uuid)
    && uuid_is_null(client->thread_uuid)) {
        if (!team)
            dprintf(client->socket, "441 {%s}", client->team_uuid);
        else if (get_channel_by_uuid(&team->channels, client->channel_uuid))
            dprintf(client->socket, "442 {%s}", client->team_uuid);
        else
            display_channel(server, client);
        return;
    }
    else if (!uuid_is_null(client->team_uuid) && !uuid_is_null(client->channel_uuid)
    && !uuid_is_null(client->thread_uuid)) {
        team = get_team_by_uuid(&server->teams, client->team_uuid);
        if (!team)
            dprintf(client->socket, "441 {%s}", client->team_uuid);
        else {
            channel = get_channel_by_uuid(&team->channels, client->channel_uuid);
            if (!channel)
                dprintf(client->socket, "442 {%s}", client->team_uuid);
            else if (!get_thread_by_uuid(&channel->threads, client->thread_uuid))
                dprintf(client->socket, "443 {%s}", client->team_uuid);
            else
                ;// display_threads(server, client);
        }
        return;
    }
    dprintf(client->socket, "413 Nothing to show\r\n");
}