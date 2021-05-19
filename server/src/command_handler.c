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

const char *command_nolog[] = {"/help\n", "/login\n", "/logout\n", NULL};
const char *command_log[] = {"/users\n", "/user\n", "/send\n", "/messages\n", "/subscribe\n",
                             "/subscribed\n", "/unsubscribe\n", "/use\n", "/create",
                             "/list\n", "/info\n", NULL};

void command_logged(server_t *server, client_t *client, char *command)
{
    void (*list_func[])(server_t *, client_t *, const char *) =
    {NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, &create,
    &list, &info, NULL};
    char *real_command = strdup(command);

    real_command = strtok(real_command, " ");
    if (!real_command)
        return;
    for (int i = 0; command_log[i]; i++)
        if (strcasecmp(real_command, command_log[i]) == 0) {
            list_func[i](server, client, command);
            return;
        }
    dprintf(client->socket,
            "Command unknown\r\n");
}

void command_without_login(server_t *server, client_t *client, char *command)
{
    void (*list_func[])(server_t *, client_t *, const char *) =
    {&help, &login, &logout};
    for (int i = 0; command_nolog[i]; i++)
        if (strcasecmp(command, command_nolog[i]) == 0) {
            list_func[i](server, client, command);
            return;
        }
    if (client->connected)
        command_logged(server, client, command);
    else
        dprintf(client->socket,
        "You're not logged, use /login[\"user_name\"]\r\n");
}

void command_handler(server_t *server, client_t *client)
{
    char *command = NULL;
    size_t len = 0;
    FILE * file = fdopen(client->socket, "r");

    (void)server;
    getline(&command, &len, file);
    command_without_login(server, client, command);
    free(command);
}