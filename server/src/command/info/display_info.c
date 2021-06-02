/*
** EPITECH PROJECT, 2021
** display_info.c
** File description:
** display_info.c
*/

#include "server.h"

void display_info_teams(server_t *server, client_t *client)
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

void display_info_channel(server_t *server, client_t *client)
{
    char *uuid = malloc(sizeof(char) * 37);
    team_t *team = get_team_by_uuid(&server->teams, client->team_uuid);
    channel_t *target = get_channel_by_uuid(&team->channels,
                                            client->channel_uuid);

    dprintf(client->socket, "113 ");
    uuid_unparse(target->uuid, uuid);
    dprintf(client->socket, "{channel}");
    dprintf(client->socket, "{%s}", uuid);
    dprintf(client->socket, "{%s}", target->name);
    dprintf(client->socket, "{%s}", target->description);
    dprintf(client->socket, "\r\n");
    free(uuid);
}

void display_info_thread(server_t *server, client_t *client)
{
    char *uuid = malloc(sizeof(char) * 37);
    team_t *team = get_team_by_uuid(&server->teams, client->team_uuid);
    channel_t *channel = get_channel_by_uuid(&team->channels,
                                             client->channel_uuid);
    thread_t *target = get_thread_by_uuid(&channel->threads,
                                          client->thread_uuid);

    dprintf(client->socket, "113 ");
    uuid_unparse(target->uuid, uuid);
    dprintf(client->socket, "{thread}");
    dprintf(client->socket, "{%s}", uuid);
    dprintf(client->socket, "{%s}", client->uuid_str);
    dprintf(client->socket, "{%s}", "TEAM");
    dprintf(client->socket, "{%s}", target->name);
    dprintf(client->socket, "{%s}", target->message->core);
    dprintf(client->socket, "\r\n");
    free(uuid);
}