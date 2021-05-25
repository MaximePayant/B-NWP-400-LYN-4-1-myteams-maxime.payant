/*
** EPITECH PROJECT, 2021
** thread.hpp
** File description:
** thread.hpp
*/

#ifndef THREAD
#define THREAD

#include "message.h"

typedef struct thread_s
{
    uuid_t uuid;
    char *name;
    message_t *message;
    struct thread_s *next;
    struct thread_s *prev;
} thread_t;

thread_t *create_thread(thread_t **first, client_t *client,
                          char *name, char *description);
thread_t *get_thread_by_uuid(thread_t **first, uuid_t target_uuid);
thread_t *get_thread_by_name(thread_t **first, char *name);

#endif //THREAD
