/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** load_channel.c
*/

#include <stdlib.h>
#include <string.h>

#include "libs/json_parser/json_parser.h"
#include "server.h"

void load_channel(team_t *team, jsnp_value_t *value)
{
    channel_t *chan = malloc(sizeof(channel_t));
    channel_t *current = team->channels;

    chan->name = strdup(get_token(value, "Name")->value->str);
    printf("Chan Name: %s\n", chan->name);
    chan->description = strdup(get_token(value, "Description")->value->str);
    uuid_parse(get_token(value, "uuid")->value->str, chan->uuid);
    chan->threads = NULL;
    for (jsnp_value_t *it =
    get_token(value, "Threads")->value->array.lh_first; it;
    it = it->next.le_next)
        load_thread(chan, it);
    chan->next = NULL;
    chan->prev = NULL;
    if (!current)
        team->channels = chan;
    else {
        while (current->next)
            current = current->next;
        current->next = chan;
        chan->prev = current;
    }
}