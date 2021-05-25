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
#include "libs/myteams/logging_server.h"

static void define_value(thread_t *new_thread, client_t *client,
char *name, char *message)
{
    int last = strlen(message) - 1;

    new_thread->next = NULL;
    new_thread->prev = NULL;
    new_thread->message = NULL;
    uuid_generate(new_thread->uuid);
    new_thread->name = strdup(name);
    message[last] = (message[last] == '\n') ? '\0' : message[last];
    create_message(&new_thread->message, client, message);
}

static void print_event(thread_t *new_thread, client_t *client)
{
    char *threads_uuid = malloc(sizeof(char) * 37);
    char *team_uuid = malloc(sizeof(char) * 37);
    char *channel_uuid = malloc(sizeof(char) * 37);
    char *user_uuid = malloc(sizeof(char) * 37);

    uuid_unparse(new_thread->uuid, threads_uuid);
    uuid_unparse(client->team_uuid, team_uuid);
    uuid_unparse(client->channel_uuid, channel_uuid);
    uuid_unparse(client->uuid, user_uuid);
    server_event_thread_created(channel_uuid, threads_uuid, user_uuid,
    new_thread->name, new_thread->message->core);
    dprintf(client->socket, "111 thread successfully created{thread}"
    "{%s}{%s}{%s}{%s}\r\n", threads_uuid, user_uuid, new_thread->name,
    new_thread->message->core);
    free(threads_uuid);
    free(team_uuid);
    free(channel_uuid);
    free(user_uuid);
}

void *check_error(client_t *client, char *name, char *message)
{
    if (strlen(name) > MAX_NAME_LENGTH) {
        dprintf(client->socket, "411 thread's name too long\r\n");
        return (NULL);
    }
    if (strlen(message) > MAX_BODY_LENGTH) {
        dprintf(client->socket, "411 thread's message too long\r\n");
        return (NULL);
    }
    return(client);
}

thread_t *create_thread(thread_t **first, client_t *client,
char *name, char *message)
{
    thread_t *new_thread = malloc(sizeof(thread_t));
    thread_t *current = *first;

    if (!check_error(client, name, message))
        return (NULL);
    define_value(new_thread, client, name, message);
    if (!current)
        *first = new_thread;
    else {
        while (current->next)
            current = current->next;
        current->next = new_thread;
        new_thread->prev = current;
    }
    print_event(new_thread, client);
    return (new_thread);
}