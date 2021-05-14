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
    char *buffer = malloc(sizeof (char) * 33);
    int status = 0;

    memset(buffer, 0, 32);
    status = read(0, buffer, 32);
    if (status == -1) {
        perror("read()");
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
        if (strcasecmp(command, "QUIT") == 0)
            quit = 1;
        send_command(client, command);
        free(command);
        if (quit)
            return;
    }
}