/*
** EPITECH PROJECT, 2021
** get_client.c
** File description:
** get_client.c
*/

#include <stddef.h>
#include "server.h"

client_t *get_client_by_sclient(server_t *server, int socket)
{
    client_t *current = server->client;

    while (current) {
        if (current->socket == socket)
            return (current);
        current = current->next;
    }
    return (NULL);
}

client_t *get_client_by_uuid(server_t *server, uuid_t target_uuid)
{
    client_t *current = server->client;

    while (current) {
        if (uuid_compare(current->uuid, target_uuid))
            return (current);
        current = current->next;
    }
    return (NULL);
}