/*
** EPITECH PROJECT, 2021
** code_102.c
** File description:
** code_102.c
*/

#include <string.h>
#include <malloc.h>
#include "libs/myteams/logging_client.h"
#include "client.h"

void code_102(const char *args)
{
    char *uuid = strstr(args, "{");
    char *name = strdup(uuid);
    char *save = name;

    name = strstr(name + 1, "{");
    uuid = strtok(uuid, "}");
    name = strtok(name, "}");
    client_event_logged_out(uuid + 1, name + 1);
    get_client(NULL)->exit = 1;
    free(save);
}