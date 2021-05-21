/*
** EPITECH PROJECT, 2021
** list.cpp
** File description:
** list.cpp
*/

#include <stdio.h>
#include <malloc.h>
#include "server.h"

#include <string.h>

static void display_teams(server_t *server, client_t *client)
{
    team_t *current = server->teams;
    int i = 0;
    char *uuid = malloc(sizeof(char) * 37);

    dprintf(client->socket, "112 \n");
    while (current) {
        uuid_unparse(current->uuid, uuid);
        dprintf(client->socket, "Team n°%d:\n", i);
        dprintf(client->socket, "\tName: %s\n", current->name);
        dprintf(client->socket, "\tUuid: %s\n", uuid);
        dprintf(client->socket, "\tDescription: %s\n", current->description);
        current = current->next;
        if (current)
            i++;
    }
    dprintf(client->socket, "\r\n");
    free(uuid);
}

static void display_channels(server_t *server, client_t *client)
{
    channel_t *current = get_team_by_uuid(&server->teams,
    client->team_uuid)->channels;
    int i = 0;
    char *uuid = malloc(sizeof(char) * 37);

    dprintf(client->socket, "112 \n");
    while (current) {
        uuid_unparse(current->uuid, uuid);
        dprintf(client->socket, "Channel n°%d:\n", i);
        dprintf(client->socket, "\tName: %s\n", current->name);
        dprintf(client->socket, "\tUuid: %s\n", uuid);
        dprintf(client->socket, "\tDescription: %s\n", current->description);
        current = current->next;
        if (current)
            i++;
    }
    dprintf(client->socket, "\r\n");
    free(uuid);
}

static void display_threads(server_t *server, client_t *client)
{
    team_t *team = get_team_by_uuid(&server->teams,
    client->team_uuid);
    channel_t *channel = get_channel_by_uuid(&team->channels,
    client->channel_uuid);
    thread_t *current = channel->threads;
    int i = 0;
    char *uuid = malloc(sizeof(char) * 37);

    dprintf(client->socket, "112 \n");
    while (current) {
        uuid_unparse(current->uuid, uuid);
        dprintf(client->socket, "Thread n°%d:\n", i);
        dprintf(client->socket, "\tName: %s\n", current->name);
        dprintf(client->socket, "\tUuid: %s\n", uuid);
        dprintf(client->socket, "\tmessage: %s\n", current->message);
        current = current->next;
        if (current)
            i++;
    }
    dprintf(client->socket, "\r\n");
    free(uuid);
}

void list(server_t *server, client_t *client, const char *command)
{
    (void)command;
    if (uuid_is_null(client->team_uuid) && uuid_is_null(client->channel_uuid)
        && uuid_is_null(client->thread_uuid)) {
        display_teams(server, client);
        return;
    }
    if (!uuid_is_null(client->team_uuid) && uuid_is_null(client->channel_uuid)
        && uuid_is_null(client->thread_uuid)) {
        display_channels(server, client);
        return;
    }
    if (!uuid_is_null(client->team_uuid) && !uuid_is_null(client->channel_uuid)
        && uuid_is_null(client->thread_uuid)) {
        display_threads(server, client);
        return;
    }
    dprintf(client->socket, "412 Nothing to show\n");
}