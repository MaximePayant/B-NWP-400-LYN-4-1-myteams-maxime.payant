/*
** EPITECH PROJECT, 2021
** command_handler.c
** File description:
** command_handler.c
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "server.h"

const char *command_nolog[] = {"help", "login", "logout"};
const char *command_log[] = {"users", "user", "send", "messages"};

void command_without_login(server_t *server, client_t *client)
{

}

void command_handler(server_t *server, client_t *client)
{
    char *command = NULL;
    size_t len = 0;
    FILE * file = fdopen(client->control_socket, "r");

    (void)server;
    getline(&command, &len, file);
    printf("%s\n", command);
    if (strcasecmp("/logout\n", command) == 0)
        delete_client(server, client->control_socket);
    free(command);
}