/*
** EPITECH PROJECT, 2021
** server.cpp
** File description:
** server.cpp
*/

#include "server.h"

server_t *get_server(server_t *server)
{
    static server_t *real_server = NULL;

    if (server)
        real_server = server;
    return (real_server);
}