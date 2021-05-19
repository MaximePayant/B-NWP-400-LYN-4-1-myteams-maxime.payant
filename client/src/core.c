/*
** EPITECH PROJECT, 2021
** core.c
** File description:
** core.c
*/

#include <string.h>
#include <unistd.h>
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

void client_core(client_t *client)
{
    char *command = NULL;
    int quit = 0;

    (void)client;
    while (1) {
        command = get_command();
        if (command == NULL)
            return;
        if (strcasecmp(command, "/logout\n") == 0)
            quit = 1;
        send_command(client, command);
        free(command);
        if (quit)
            return;
    }
}