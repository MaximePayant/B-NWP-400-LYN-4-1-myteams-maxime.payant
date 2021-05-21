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
    uuid_generate(new_channel->uuid);
    new_channel->name = strdup(name);
    description[last] = (description[last] == '\n') ? '\0' : description[last];
    new_channel->description = strdup(description);
}

static void free_mem(char *str1, char *str2)
{
    free(str1);
    free(str2);
}

channel_t *create_channel(channel_t **first, client_t *client,
char *name, char *description)
{
    channel_t *new_channel = malloc(sizeof(channel_t));
    channel_t *current = *first;
    char *channels_uuid = malloc(sizeof(char) * 37);
    char *client_uuid = malloc(sizeof(char) * 37);

    if (strlen(name) > MAX_NAME_LENGTH) {
        free_mem(channels_uuid, client_uuid);
        dprintf(client->socket, "411 channel's name too long\r\n");
        return (NULL);
    }
    if (strlen(description) > MAX_DESCRIPTION_LENGTH) {
        free_mem(channels_uuid, client_uuid);
        dprintf(client->socket, "411 channel's description too long\r\n");
        return (NULL);
    }
    define_value(new_channel, name, description);
    uuid_unparse(new_channel->uuid, channels_uuid);
    uuid_unparse(client->uuid, client_uuid);
    if (!current)
        *first = new_channel;
    else {
        while (current->next)
            current = current->next;
        current->next = new_channel;
        new_channel->prev = current;
    }
    server_event_channel_created(channels_uuid, new_channel->name, client_uuid);
    free_mem(channels_uuid, client_uuid);
    dprintf(client->socket, "111 channel successfully created\r\n");
    return (new_channel);
}