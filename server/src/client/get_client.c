/*
** EPITECH PROJECT, 2021
** get_client.c
** File description:
** get_client.c
*/

#include <stddef.h>
#include "server.h"

client_t *get_client_by_sclient(server_t *ftp, int socket)
{
    client_t *current = ftp->client;

    while (current) {
        if (current->socket == socket)
            return (current);
        current = current->next;
    }
    return (NULL);
}