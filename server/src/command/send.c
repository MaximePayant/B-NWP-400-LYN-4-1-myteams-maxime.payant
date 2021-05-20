/*
** EPITECH PROJECT, 2021
** Delivery
** File description:
** send
*/

#include <stdio.h>
#include "server.h"

void send_message(server_t *server, client_t *client, const char *command)
{
    char *new_command = strdup(command);
    char *target = NULL;
    char *message = NULL;

    strtok(new_command, " ");
    target = strtok(NULL, " ");
    message = strtok(NULL, " ");

    dprintf(client->socket, "Send message %s"\r\n");
    delete_client(server, client->socket);
}