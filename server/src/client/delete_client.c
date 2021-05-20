/*
** EPITECH PROJECT, 2021
** delete_client.c
** File description:
** delete_client.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include "server.h"

static void close_and_free(client_t *delete)
{
    if (delete->socket != -1)
        close(delete->socket);
    close(delete->socket);
    free(delete->user_name);
    free(delete);
    printf("[SERVER] Client disconnected\n");
}

void delete_client(server_t *ftp, int socket)
{
    client_t *current = ftp->client;
    client_t *delete = NULL;

    while (current) {
        if ((current->next && current->next->socket == socket) ||
            current->socket == socket)
            break;
        current = current->next;
    }
    if (!current)
        return;
    delete = (current->next) ? current->next : current;
    if (current->next)
        current->next = current->next->next;
    else if (ftp->client == delete)
        ftp->client = NULL;
    close_and_free(delete);
}