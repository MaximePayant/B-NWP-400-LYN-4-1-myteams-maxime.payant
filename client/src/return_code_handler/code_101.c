/*
** EPITECH PROJECT, 2021
** code_101.c
** File description:
** code_101.c
*/

#include <string.h>
#include <malloc.h>
#include "libs/myteams/logging_client.h"

void code_101(const char *args)
{
    char *uuid = strstr(args, "{");
    char *name = strdup(uuid);
    char *save = name;

    name = strstr(name + 1, "{");
    uuid = strtok(uuid, "}");
    name = strtok(name, "}");
    client_event_logged_in(uuid + 1, name + 1);
    free(save);
}