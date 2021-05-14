/*
** EPITECH PROJECT, 2021
** command_handler.cpp
** File description:
** command_handler.cpp
*/

#include <stdio.h>
#include <unistd.h>
#include "client.h"

int send_command(client_t *client, char *command)
{
    dprintf(client->socket, "%s\r\n", command);
    return (0);
}