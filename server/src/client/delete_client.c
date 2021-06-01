/*
** EPITECH PROJECT, 2021
** delete_client.c
** File description:
** delete_client.c
*/

#include <unistd.h>
#include <stdio.h>
#include "server.h"

static void close_and_free(client_t *delete)
{
    fclose(delete->file);
    if (delete->socket != -1)
        close(delete->socket);
    close(delete->socket);
    free(delete->user_name);
    free(delete);
    printf("[SERVER] Client disconnected\n");
}

void delete_client(server_t *server, uuid_t uuid)
{
    client_t *delete = get_client_by_uuid(server, uuid);

    if (delete->prev)
        delete->prev->next = delete->next;
    else
        server->client = delete->next;
    if (delete->next)
        delete->next->prev = delete->prev;
    close_and_free(delete);
}