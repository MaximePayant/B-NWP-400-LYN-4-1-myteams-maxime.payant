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

void use(server_t *server, client_t *client, const char *command)
{
    char *new_command = strdup(command);
    char *value = strtok(new_command, " ");

    (void)server;
    value = strtok(NULL, " ");
    if (!value || strcasecmp(value, "(null)") == 0) {
        uuid_clear(client->team_uuid);
        uuid_clear(client->channel_uuid);
        uuid_clear(client->thread_uuid);
        dprintf(client->socket, "110 You don't have any target\r\n");
        free(new_command);
        return;
    }
    uuid_parse(correct_uuid(value), client->team_uuid);
    value = strtok(NULL, " ");
    if (!value) {
        dprintf(client->socket, "110 You target a team\r\n");
        free(new_command);
        return;
    }
    uuid_parse(correct_uuid(value), client->channel_uuid);
    value = strtok(NULL, " ");
    if (!value) {
        dprintf(client->socket, "110 You target a channel\r\n");
        free(new_command);
        return;
    }
    uuid_parse(correct_uuid(value), client->thread_uuid);
    free(new_command);
    dprintf(client->socket, "110 You target a thread\r\n");
}