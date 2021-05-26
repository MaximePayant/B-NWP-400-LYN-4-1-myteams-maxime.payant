/*
** EPITECH PROJECT, 2021
** thread_create.c
** File description:
** thread_create.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "channels.h"
#include "libs/myteams/logging_server.h"

static void define_value(channel_t *new_channel, char *name, char *description)
{
    int last = strlen(description) - 1;

    new_channel->next = NULL;
    new_channel->prev = NULL;
    new_channel->threads = NULL;
    uuid_generate(new_channel->uuid);
    new_channel->name = strdup(name);
    description[last] = (description[last] == '\n') ? '\0' : description[last];
    new_channel->description = strdup(description);
}

static void *check_error(client_t *client, channel_t **first, char *name, char *description)
{
    if (get_channel_by_name(first, name))
        return (dprintf(client->socket, "439"), NULL);
    if (strlen(name) > MAX_NAME_LENGTH) {
        dprintf(client->socket, "411 channel's name too long\r\n");
        return (NULL);
    }
    if (strlen(description) > MAX_DESCRIPTION_LENGTH) {
        dprintf(client->socket, "411 channel's description too long\r\n");
        return (NULL);
    }
    return (client);
}

static void print_event(channel_t *new_channel, client_t *client)
{
    char *channels_uuid = malloc(sizeof(char) * 37);
    char *team_uuid = malloc(sizeof(char) * 37);

    uuid_unparse(new_channel->uuid, channels_uuid);
    uuid_unparse(client->team_uuid, team_uuid);
    server_event_channel_created(team_uuid, channels_uuid, new_channel->name);
    dprintf(client->socket, "111 Channel successfully created{channel}"
    "{%s}{%s}{%s}\r\n", channels_uuid, new_channel->name,
    new_channel->description);
}

channel_t *create_channel(channel_t **first, client_t *client,
char *name, char *description)
{
    channel_t *new_channel = malloc(sizeof(channel_t));
    channel_t *current = *first;

    if (!check_error(client, first, name, description)) {
        free(new_channel);
        return (NULL);
    }
    define_value(new_channel, name, description);
    if (!current)
        *first = new_channel;
    else {
        while (current->next)
            current = current->next;
        current->next = new_channel;
        new_channel->prev = current;
    }
    print_event(new_channel, client);
    return (new_channel);
}