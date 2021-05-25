/*
** EPITECH PROJECT, 2021
** list.cpp
** File description:
** list.cpp
*/

#include <stdio.h>
#include <malloc.h>
#include "server.h"

static void display_teams(server_t *server, client_t *client)
{
    team_t *current = server->teams;
    char *uuid = malloc(sizeof(char) * 37);

    dprintf(client->socket, "112 {team}");
    while (current) {
        uuid_unparse(current->uuid, uuid);
        dprintf(client->socket, "{%s}", uuid);
        dprintf(client->socket, "{%s}", current->name);
        dprintf(client->socket, "{%s}\n", current->description);
        current = current->next;
    }
    dprintf(client->socket, "\r\n");
    free(uuid);
}

static void display_channels(server_t *server, client_t *client)
{
    channel_t *current = get_team_by_uuid(&server->teams,
    client->team_uuid)->channels;
    char *uuid = malloc(sizeof(char) * 37);

    dprintf(client->socket, "112 {channel}\n");
    while (current) {
        uuid_unparse(current->uuid, uuid);
        dprintf(client->socket, "{%s}", uuid);
        dprintf(client->socket, "{%s}", current->name);
        dprintf(client->socket, "{%s}\n", current->description);
        current = current->next;
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
    char *uuid = malloc(sizeof(char) * 37);
    char *client_uuid = malloc(sizeof(char) * 37);

    dprintf(client->socket, "112 {thread}\n");
    while (current) {
        uuid_unparse(current->uuid, uuid);
        uuid_unparse(client->uuid, client_uuid);
        dprintf(client->socket, "{%s}", uuid);
        dprintf(client->socket, "{%s}", client_uuid);
        dprintf(client->socket, "{%s}", current->name);
        dprintf(client->socket, "{%s}\n", current->message->core);
        current = current->next;
    }
    dprintf(client->socket, "\r\n");
    free(uuid);
}

static void display_messages(server_t *server, client_t *client)
{
    team_t *team = get_team_by_uuid(&server->teams, client->team_uuid);
    channel_t *channel = get_channel_by_uuid(&team->channels,
                                             client->channel_uuid);
    thread_t *thread = get_thread_by_uuid(&channel->threads, client->thread_uuid);
    message_t *current = thread->message;
    char *thread_uuid = malloc(sizeof(char) * 37);
    char *client_uuid = malloc(sizeof(char) * 37);

    dprintf(client->socket, "112 {message}\n");
    while (current) {
        uuid_unparse(client->uuid, client_uuid);
        uuid_unparse(client->thread_uuid, thread_uuid);
        dprintf(client->socket, "{%s}", thread_uuid);
        dprintf(client->socket, "{%s}", client_uuid);
        dprintf(client->socket, "{%s}", "TIMER");
        dprintf(client->socket, "{%s}\n", current->core);
        current = current->next;
    }
    dprintf(client->socket, "\r\n");
    free(thread_uuid);
    free(client_uuid);
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
    if (!uuid_is_null(client->team_uuid) && !uuid_is_null(client->channel_uuid)
        && !uuid_is_null(client->thread_uuid)) {
        display_messages(server, client);
        return;
    }
    dprintf(client->socket, "412 Nothing to show\n");
}