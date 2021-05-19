/*
** EPITECH PROJECT, 2021
** core.c
** File description:
** core.c
*/

#include <stddef.h>
#include <stdio.h>
#include "server.h"

int select_socket(server_t *server, fd_set *set)
{
    int select_return = 0;

    select_return = select(FD_SETSIZE, set, NULL, NULL, NULL);
    if (select_return == -1) {
        perror("select()");
        return (1);
    } else if (select_return > 0) {
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (!FD_ISSET(i, set))
                continue;
            if (i == server->server_socket)
                create_new_client(server);
            else
                command_handler(server, get_client_by_sclient(server, i));
        }
    }
    return (0);
}

void update_set(server_t *server, fd_set *set)
{
    client_t *current = server->client;

    FD_ZERO(set);
    FD_SET(server->server_socket, set);
    while (current) {
        FD_SET(current->socket, set);
        current = current->next;
    }
}

void server_core(server_t *server)
{
    fd_set set = (fd_set){ 0 };
    int value = -1;

    while (1) {
        update_set(server, &set);
        value = select_socket(server, &set);
        if (value == 1)
            return;
    }
}