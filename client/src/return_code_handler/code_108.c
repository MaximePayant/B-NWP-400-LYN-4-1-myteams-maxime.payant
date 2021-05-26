/*
** EPITECH PROJECT, 2021
** code_108.c
** File description:
** code_108.c
*/

#include <string.h>
#include <malloc.h>
#include "libs/myteams/logging_client.h"

void code_108(const char *args)
{
    char *uuid = strstr(args, "{");
    char *team_uuid = strdup(uuid);
    char *save = team_uuid;

    team_uuid = strstr(team_uuid + 1, "{");
    uuid = strtok(uuid, "}");
    team_uuid = strtok(team_uuid, "}");
    client_print_subscribed(uuid + 1, team_uuid + 1);
    free(save);
}