/*
** EPITECH PROJECT, 2021
** code_109.c
** File description:
** code_109.c
*/

#include <string.h>
#include <malloc.h>
#include "libs/myteams/logging_client.h"


void code_109(const char *args)
{
    char *uuid = strstr(args, "{");
    char *team_uuid = strdup(uuid);
    char *save = team_uuid;

    team_uuid = strstr(team_uuid + 1, "{");
    uuid = strtok(uuid, "}");
    team_uuid = strtok(team_uuid, "}");
    client_print_unsubscribed(uuid + 1, team_uuid + 1);
    free(save);
}