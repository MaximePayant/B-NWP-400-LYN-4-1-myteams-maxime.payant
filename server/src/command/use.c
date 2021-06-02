/*
** EPITECH PROJECT, 2021
** use.c
** File description:
** use.c
*/

#include <string.h>
#include <malloc.h>
#include "server.h"

char *correct_uuid(char *uuid)
{
    for (int i = 0; uuid[i] != '\0'; i++)
        if (uuid[i] == '\n')
            uuid[i] = '\0';
    return (uuid);
}

static void define_target(client_t *client, char **args)
{
    uuid_parse(correct_uuid(args[0]), client->team_uuid);
    if (!args[1]) {
        dprintf(client->socket, "110 You target a team\r\n");
        return;
    }
    uuid_parse(correct_uuid(args[1]), client->channel_uuid);
    if (!args[2]) {
        dprintf(client->socket, "110 You target a channel\r\n");
        return;
    }
    uuid_parse(correct_uuid(args[2]), client->thread_uuid);
    dprintf(client->socket, "110 You target a thread\r\n");
}

void use(server_t *server, client_t *client, const char *command)
{
    char **args = get_params(command);

    (void)server;
    uuid_clear(client->team_uuid);
    uuid_clear(client->channel_uuid);
    uuid_clear(client->thread_uuid);
    if (!args[0] || strcasecmp(args[0], "(null)") == 0) {
        dprintf(client->socket, "110 You don't have any target\r\n");
        return;
    }
    define_target(client, args);
}