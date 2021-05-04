/*
** EPITECH PROJECT, 2021
** client_init.c
** File description:
** client_init.c
*/

#include <stddef.h>
#include <malloc.h>
#include "server.h"

void init_value(client_t *new_client)
{
    new_client->connected = 0;
    new_client->user_name = NULL;
    new_client->next = NULL;
}

client_t *create_new_client(server_t *server)
{
    client_t *new_client = malloc(sizeof(client_t));
    client_t *current = server->client;

    new_client->control_socket = accept(server->server_socket,
                                        (struct sockaddr *)&server->sock, &server->sock_size);
    if (new_client->control_socket < 0) {
        perror("accept");
        free(new_client);
        return (NULL);
    }
    init_value(new_client);
    while (current && current->next)
        current = current->next;
    if (current)
        current->next = new_client;
    else
        server->client = new_client;
    FD_SET(new_client->control_socket, &server->set_save);
    return (new_client);
}