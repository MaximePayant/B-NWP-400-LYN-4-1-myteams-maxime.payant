/*
** EPITECH PROJECT, 2021
** code_111.c
** File description:
** code_111.c
*/

#include <string.h>
#include "client.h"
#include "libs/myteams/logging_client.h"

void code_112(const char *args)
{
    char **arg = get_return_args(args);

    if (strcmp(arg[0], "team") == 0) {
        for (int i = 1; arg[i]; i++) {
            client_print_teams(arg[i], arg[i + 1], arg[i + 2]);
            i += 2;
        }
    }
    if (strcmp(arg[0], "channel") == 0) {
        for (int i = 1; arg[i]; i++) {
            client_team_print_channels(arg[i], arg[i + 1], arg[i + 2]);
            i += 2;
        }
    }
    if (strcmp(arg[0], "thread") == 0) {
        for (int i = 1; arg[i]; i++) {
            client_channel_print_threads(arg[i], arg[i + 1], time(NULL), arg[i + 2], arg[i + 3]);
            i += 3;
        }
    }
    if (strcmp(arg[0], "message") == 0) {
        for (int i = 1; arg[i]; i++) {
            client_thread_print_replies(arg[i], arg[i + 1], time(NULL), arg[i + 3]);
            i += 3;
        }
    }
}