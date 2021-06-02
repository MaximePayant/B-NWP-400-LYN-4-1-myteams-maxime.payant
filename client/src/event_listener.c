/*
** EPITECH PROJECT, 2021
** event_listener.cpp
** File description:
** event_listener.cpp
*/

#include "client.h"

void update_set(client_t *client, fd_set *set)
{
    FD_ZERO(set);
    FD_SET(0, set);
    FD_SET(client->socket, set);
}