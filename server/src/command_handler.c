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

const char *command_nolog[] = {"HELP", "LOGIN", "LOGOUT", NULL};
const char *command_log[] = {"USERS", "USER", "SEND", "MSG", "SUBC", "UNSUB",
                             "SUBED", "USE", "CREA", "LIST", "INFO", NULL};

char *str_clean(char *string)
{
    for (int i = 0; string[i] != '\0'; i++)
        if (string[i] == '\r')
            string[i] = '\0';
    return (string);
}

void command_logged(server_t *server, client_t *client, char *command)
{
    void (*list_func[])(server_t *, client_t *, const char *) =
    {NULL, NULL, NULL, NULL, &subscribe, &unsubscribe, &subscribed, &use,
    &create, &list, &info, NULL};
    char *real_command = strdup(command);

    real_command = strtok(real_command, " ");
    if (!real_command)
        return;
    for (int i = 0; command_log[i]; i++)
        if (strstr(command, command_log[i]) == command) {
            list_func[i](server, client, command);
            free(real_command);
            return;
        }
    dprintf(client->socket, "404 Command unknown\r\n");
    free(real_command);
}

void command_without_login(server_t *server, client_t *client, char *command)
{
        void (*list_func[])(server_t *, client_t *, const char *) =
        {&help, &login, &logout};

    for (int i = 0; command_nolog[i]; i++)
        if (strstr(command, command_nolog[i]) == command) {
            list_func[i](server, client, command);
            return;
        }
    if (client->connected)
        command_logged(server, client, command);
    else
        dprintf(client->socket,
        "402 You're not logged, use /login[\"user_name\"]\r\n");
}

void command_handler(server_t *server, client_t *client)
{
    char *command = "\0";
    size_t len = 0;
    FILE * file = fdopen(client->socket, "r");
    char *complete = malloc(sizeof(char));

    (void)server;
    complete[0] = '\0';
    while (!strstr(complete, "\r\n")) {
        getline(&command, &len, file);
        complete = realloc(complete, strlen(complete) + strlen(command));
        strcat(complete, command);
    }
    command_without_login(server, client, str_clean(complete));
    free(command);
}