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
    new_message->time = time(NULL);
}

static void send_event(server_t *server, message_t *message, client_t *client, char *thread_uuid)
{
    client_t *current = server->client;
    char *team_uuid = malloc(sizeof(char) * 37);

    uuid_unparse(client->team_uuid, team_uuid);
    while (current) {
        if (!current->connected) {
            current = current->next;
            continue;
        }
        dprintf(current->socket, "222 New team created{reply}{%s}"
        "{%s}{%s}{%s}\r\n", team_uuid, thread_uuid, client->uuid_str, message->core);
        current = current->next;
    }
}

void print_new_reply(message_t *message, client_t *client)
{
    char *thread_uuid = malloc(sizeof(char) * 37);
    char buff[20];

    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&message->time));
    uuid_unparse(client->thread_uuid, thread_uuid);
    server_event_thread_new_reply(thread_uuid, client->uuid_str, message->core);
    dprintf(client->socket, "111 thread successfully created{message}{%s}{%s}{%s}{%s}\r\n",
    thread_uuid, client->uuid_str, buff, message->core);
    send_event(get_server(NULL), message, client, thread_uuid);
    free(thread_uuid);
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