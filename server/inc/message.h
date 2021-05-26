/*
** EPITECH PROJECT, 2021
** message.h
** File description:
** message.h
*/

#ifndef MESSAGE
#define MESSAGE

#include <uuid/uuid.h>
#include "server.h"

typedef struct message_s
{
    char *core;
    uuid_t author;
    time_t time;
    struct message_s *prev;
    struct message_s *next;
} message_t;

message_t *create_message(message_t **first, client_t *client,
const char *body);

#endif //MESSAGE
