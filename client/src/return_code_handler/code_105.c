/*
** EPITECH PROJECT, 2021
** code_111.c
** File description:
** code_111.c
*/

#include <string.h>
#include "client.h"
#include "libs/myteams/logging_client.h"

void code_105(const char *args)
{
    char *uuid = strstr(args, "{");
    char *message = strdup(uuid);
    int save;

    message = strstr(message + 1, "{");
    uuid = strtok(uuid, "}");
    save = args[2];
    client_print_user(message+1, uuid+1, save);
}