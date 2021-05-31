/*
** EPITECH PROJECT, 2021
** core.c
** File description:
** core.c
*/

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "client.h"

int on_command(char *command)
{
    char *line_break = strchr(command, '\n');

    if (strlen(command) == 0)
        return (0);
    if (line_break == NULL)
        return (0);
    if (strchr(line_break + 1, '\n') != NULL)
        return (0);
    for (int i = 0; command[i] != '\0'; i++)
        if (command[i] == '\n')
            command[i] = '\0';
    return (1);
}

char *get_command()
{
    char *buffer = NULL;
    size_t size = 0;
    int status = 0;

    status = (int)getline(&buffer, &size, stdin);
    if (status == -1) {
        perror("getline");
        return (NULL);
    } else {
        if (on_command(buffer))
            return (buffer);
    }
    return (NULL);
}

int command_handler_send(client_t *client)
{
    char *command = NULL;

    command = get_command();
    if (command == NULL)
        return (1);
    send_command(client, command);
    command_handler(client);
    free(command);
    return (0);
}

int select_socket(client_t *client, fd_set *set)
{
    int select_return = 0;

    select_return = select(FD_SETSIZE, set, NULL, NULL, NULL);
    if (select_return == -1) {
        perror("select");
        return (1);
    } else {
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (!FD_ISSET(i, set))
                continue;
            if (i == client->socket)
                command_handler(client);
            else
                return (command_handler_send(client));
        }

    }
    return (0);
}

void client_core(client_t *client)
{
    fd_set set = (fd_set){ 0 };

    while (!client->exit) {
        update_set(client, &set);
        if (select_socket(client, &set))
            return;
    }
}