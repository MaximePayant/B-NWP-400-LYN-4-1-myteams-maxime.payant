/*
** EPITECH PROJECT, 2021
** signal_handler.c
** File description:
** signal_handler.c
*/

#include <stdlib.h>
#include "server.h"

void signalHandler(int signum)
{
    server_t *server = get_server(NULL);
    client_t *current = server->client;

    (void) signum;
    save(server);
    while (current) {
        dprintf(current->socket, "222 {leave}\r\n");
        current = current->next;
    }
    exit(0);
}

