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
        }
    }
    return (0);
}

void server_core(server_t *server)
{
    fd_set set = (fd_set){ 0 };
    int value = -1;

    FD_SET(server->server_socket, &server->set_save);
    while (1) {
        set = server->set_save;
        value = select_socket(server, &set);
        if (value == 1)
            return;
    }
}