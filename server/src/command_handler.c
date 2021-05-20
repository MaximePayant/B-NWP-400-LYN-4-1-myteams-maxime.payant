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

const char *command_nolog[] = {"/help", "/login", "/logout", NULL};
const char *command_log[] = {"/users", "/user", "/send", "/messages",
                             "/subscribe", "/subscribed", "/unsubscribe",
                             "/use", "/create", "/list", "/info", NULL};

char *str_clean(char *string)
{
    for (int i = 0; string[i] != '\0'; i++)
        if (string[i] == '\n')
            string[i] = '\0';
    return (string);
}

void command_logged(server_t *server, client_t *client, char *command)
{
    void (*list_func[])(server_t *, client_t *, const char *) =
    {NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, &use, &create,
    &list, &info, NULL};
    char *real_command = strdup(command);

    real_command = strtok(real_command, " ");
    if (!real_command)
        return;
    for (int i = 0; command_log[i]; i++)
        if (strcasecmp(real_command, command_log[i]) == 0) {
            list_func[i](server, client, command);
            free(real_command);
            return;
        }
    dprintf(client->socket,
            "Command unknown\r\n");
    free(real_command);
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
    command_without_login(server, client, str_clean(command));
    free(command);
}