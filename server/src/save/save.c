/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** save.c
*/

#include <stdlib.h>

#include "libs/json_parser/json_parser.h"
#include "server.h"

static void save_message(message_t *mess, jsnp_token_t *array)
{
    jsnp_value_t *obj = array_emplace_object_back(array->value);
    jsnp_token_t *cttime = NULL;
    char *uuid = malloc(sizeof(char) * 37);
    struct tm *ltime = localtime(&mess->time);

    uuid_unparse(mess->author, uuid);
    object_emplace_string_back(obj, "Author uuid", uuid);
    object_emplace_string_back(obj, "Body", mess->core);
    cttime = object_emplace_object_back(obj, "Creation time");
    object_emplace_primitive_back(cttime->value, "sec", ltime->tm_sec);
    object_emplace_primitive_back(cttime->value, "min", ltime->tm_min);
    object_emplace_primitive_back(cttime->value, "hour", ltime->tm_hour);
    object_emplace_primitive_back(cttime->value, "mday", ltime->tm_mday);
    object_emplace_primitive_back(cttime->value, "wday", ltime->tm_wday);
    object_emplace_primitive_back(cttime->value, "yday", ltime->tm_yday);
    object_emplace_primitive_back(cttime->value, "mon", ltime->tm_mon);
    object_emplace_primitive_back(cttime->value, "year", ltime->tm_year);
    object_emplace_primitive_back(cttime->value, "isdst", ltime->tm_isdst);
}

static void save_thread(thread_t *thrd, jsnp_token_t *array)
{
    jsnp_value_t *obj = array_emplace_object_back(array->value);
    char *uuid = malloc(sizeof(char) * 37);
    jsnp_token_t *mess_array = NULL;

    uuid_unparse(thrd->uuid, uuid);
    object_emplace_string_back(obj, "Name", thrd->name);
    object_emplace_string_back(obj, "uuid", uuid);
    mess_array = object_emplace_array_back(obj, "Messages");
    for (message_t *it = thrd->message; it; it = it->next)
        save_message(it, mess_array);
    free(uuid);
}

static void save_channel(channel_t *chan, jsnp_token_t *array)
{
    jsnp_value_t *obj = array_emplace_object_back(array->value);
    char *uuid = malloc(sizeof(char) * 37);
    jsnp_token_t *thrd_array = NULL;

    uuid_unparse(chan->uuid, uuid);
    object_emplace_string_back(obj, "Name", chan->name);
    object_emplace_string_back(obj, "Description", chan->description);
    object_emplace_string_back(obj, "uuid", uuid);
    thrd_array = object_emplace_array_back(obj, "Threads");
    for (thread_t *it = chan->threads; it; it = it->next)
        save_thread(it, thrd_array);
    free(uuid);
}

static void save_team(team_t *team, jsnp_token_t *array)
{
    jsnp_value_t *obj = array_emplace_object_back(array->value);
    char *uuid = malloc(sizeof(char) * 37);
    jsnp_token_t *sub_array = NULL;
    jsnp_token_t *chan_array = NULL;

    uuid_unparse(team->uuid, uuid);
    object_emplace_string_back(obj, "Name", team->name);
    object_emplace_string_back(obj, "Description", team->description);
    object_emplace_string_back(obj, "uuid", uuid);
    sub_array = object_emplace_array_back(obj, "Subscribers");
    chan_array = object_emplace_array_back(obj, "Channels");
    for (list_uuid *it = team->list_uuid; it; it = it->next)
        array_emplace_string_back(sub_array->value, it->string);
    for (channel_t *it = team->channels; it; it = it->next)
        save_channel(it, chan_array);
    free(uuid);
}

void save(server_t *server)
{
    jsnp_t *jsnp = create_jsnp();
    jsnp_token_t *team_array = object_emplace_array_front(jsnp->value, "Teams");

    for (team_t *it = server->teams; it; it = it->next)
        save_team(it, team_array);
    write_jsnp(jsnp, "save/server.json");
    free(jsnp);
}