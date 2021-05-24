/*
** EPITECH PROJECT, 2021
** code_111.c
** File description:
** code_111.c
*/

#include <string.h>
#include "client.h"
#include "libs/myteams/logging_client.h"

void code_111(const char *args)
{
    char **list_args = get_return_args(args);

    if (strcmp(list_args[0], "team") == 0)
        client_print_team_created(list_args[1], list_args[2], list_args[3]);
    if (strcmp(list_args[0], "channel") == 0)
        client_print_channel_created(list_args[1], list_args[2], list_args[3]);
    if (strcmp(list_args[0], "thread") == 0)
        client_print_thread_created(list_args[1], list_args[2], time(NULL), list_args[3], list_args[4]);
}