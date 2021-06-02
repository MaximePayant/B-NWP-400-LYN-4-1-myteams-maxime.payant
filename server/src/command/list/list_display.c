/*
** EPITECH PROJECT, 2021
** list_display.c
** File description:
** list_display.c
*/

#include "server.h"

void display_list_teams(server_t *server, client_t *client)
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

void display_list_channels(server_t *server, client_t *client)
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

void display_list_threads(server_t *server, client_t *client)
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

void display_list_messages(server_t *server, client_t *client)
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

