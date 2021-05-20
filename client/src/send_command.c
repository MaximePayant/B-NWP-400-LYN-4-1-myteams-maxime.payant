/*
** EPITECH PROJECT, 2021
** send_command.c
** File description:
** send_command.c
*/

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "client.h"

const char *base_command[] = {"/help", "/login", "/logout",
                             "/users", "/user", "/send", "/messages",
                             "/subscribe", "/subscribed", "/unsubscribe",
                             "/use", "/create", "/list", "/info", NULL};
const char *real_command[] = {"HELP", "LOG", "OUT", "USERS", "USER", "SEND",
                              "MSG", "SUB", "UNSUB", "SUBED", "USE", "CREA",
                              "LIST", "INFO", NULL};

void send_command(client_t *client, char *command)
{
    char *args = NULL;
    int space = -1;

    for (int i = 0; command[i] != '\0'; i++)
        if (command[i] == ' ') {
            space = i + 1;
            break;
        }
    args = strdup(command + space);
    for (int i = 0; base_command[i]; i++) {
        if (strstr(command, base_command[i]) == command)
            dprintf(client->socket, "%s %s\r\n", real_command[i], args);
    }
}