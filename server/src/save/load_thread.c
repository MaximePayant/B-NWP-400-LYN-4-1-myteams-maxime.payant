/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** load_thread.c
*/

#include <stdlib.h>
#include <string.h>

#include "libs/json_parser/json_parser.h"
#include "server.h"

void load_message(thread_t *thrd, jsnp_value_t *value)
{
    message_t *mess = malloc(sizeof(message_t));
    message_t *current = thrd->message;

    uuid_parse(get_token(value, "Author uuid")->value->str, mess->author);
    mess->core = strdup(get_token(value, "Body")->value->str);
    mess->time = string_to_time(get_token(value, "Creation time")->value->str);
    mess->next = NULL;
    mess->prev = NULL;
    if (!current)
        thrd->message = mess;
    else {
        while (current->next)
            current = current->next;
        current->next = mess;
        mess->prev = current;
    }
}

void load_thread(channel_t *chan, jsnp_value_t *value)
{
    thread_t *thrd = malloc(sizeof(thread_t));
    thread_t *current = chan->threads;

    thrd->name = strdup(get_token(value, "Name")->value->str);
    uuid_parse(get_token(value, "uuid")->value->str, thrd->uuid);
    for (jsnp_value_t *it =
    get_token(value, "Messages")->value->array.lh_first;
    it; it = it->next.le_next)
        load_message(thrd, it);
    thrd->next = NULL;
    thrd->prev = NULL;
    if (!current)
        chan->threads = thrd;
    else {
        while (current->next)
            current = current->next;
        current->next = thrd;
        thrd->prev = current;
    }
}