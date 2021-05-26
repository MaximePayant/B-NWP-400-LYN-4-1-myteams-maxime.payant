/*
** EPITECH PROJECT, 2021
** message_create.c
** File description:
** message_create.c
*/

#include <malloc.h>
#include <string.h>
#include "server.h"
#include "message.h"
#include "libs/myteams/logging_server.h"

static void define_value(message_t *new_message, client_t *client,
const char *body)
{
    new_message->time = time(NULL);
    uuid_copy(new_message->author, client->uuid);
    new_message->core = strdup(body);
    new_message->prev = NULL;
    new_message->next = NULL;
}

void print_new_reply(message_t *message, client_t *client)
{
    char *thread_uuid = malloc(sizeof(char) * 37);
    char *client_uuid = malloc(sizeof(char) * 37);

    uuid_unparse(client->uuid, client_uuid);
    uuid_unparse(client->thread_uuid, thread_uuid);
    server_event_thread_new_reply(thread_uuid, client_uuid, message->core);
    dprintf(client->socket, "111 thread successfully created{message}{%s}{%s}{%s}{%s}\r\n",
            thread_uuid, client_uuid, "TIME", message->core);
    free(thread_uuid);
    free(client_uuid);
}

message_t *create_message(message_t **first, client_t *client, const char *body)
{
    message_t *new_message = malloc(sizeof(message_t));
    message_t *current = *first;

    if (strlen(body) > MAX_BODY_LENGTH) {
        free(new_message);
        dprintf(client->socket, "411 message's length too long(%d max)"
        "\r\n", MAX_BODY_LENGTH);
        return (NULL);
    }
    define_value(new_message, client, body);
    if (!current)
        *first = new_message;
    else {
        while (current->next)
            current = current->next;
        current->next = new_message;
        new_message->prev = current;
    }
    return (new_message);
}