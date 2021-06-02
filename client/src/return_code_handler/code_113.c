/*
** EPITECH PROJECT, 2021
** code_101.c
** File description:
** code_101.c
*/

#include <string.h>
#include "libs/myteams/logging_client.h"
#include "client.h"

void code_113(const char *args)
{
    char **arg = get_return_args(args);

    if (strcmp(arg[0], "team") == 0)
        for (int i = 1; arg[i]; i++) {
            client_print_team(arg[i], arg[i + 1], arg[i + 2]);
            i += 2;
        }
    if (strcmp(arg[0], "channel") == 0)
        for (int i = 1; arg[i]; i++) {
            client_print_channel(arg[i], arg[i + 1], arg[i + 2]);
            i += 2;
        }
    if (strcmp(arg[0], "thread") == 0)
        for (int i = 1; arg[i]; i++) {
            client_print_thread(arg[i], arg[i + 1], time(NULL),
            arg[i + 3], arg[i + 4]);
            i += 4;
        }
}