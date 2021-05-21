/*
** EPITECH PROJECT, 2021
** channels.h
** File description:
** channels.h
*/

#ifndef CHANNELS
#define CHANNELS

#include "thread.h"

typedef struct channel_s {
    uuid_t uuid;
    char *name;
    char *description;
    thread_t *threads;
    struct channel_s *next;
    struct channel_s *prev;
} channel_t;

channel_t *create_channel(channel_t **first, client_t *client,
char *name, char *description);
channel_t *get_channel_by_uuid(channel_t **first, uuid_t target_uuid);
channel_t *get_channel_by_name(channel_t **first, char *name);

#endif //CHANNELS
