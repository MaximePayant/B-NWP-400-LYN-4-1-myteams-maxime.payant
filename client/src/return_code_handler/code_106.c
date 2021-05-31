/*
** EPITECH PROJECT, 2021
** code_111.c
** File description:
** code_111.c
*/

#include <string.h>
#include <stdlib.h>
#include "client.h"
#include "libs/myteams/logging_client.h"

void code_106(const char *args)
{
    char *uuid = strstr(args, "{");
    char *message = strdup(uuid);
    char *save = message;

    message = strstr(message + 1, "{");
    uuid = strtok(uuid, "}");
    message = strtok(message, "}");
    client_event_private_message_received(uuid+1, message+1);
    free(save);
}