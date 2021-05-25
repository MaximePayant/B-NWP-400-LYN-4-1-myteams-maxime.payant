/*
** EPITECH PROJECT, 2021
** code_111.c
** File description:
** code_111.c
*/

#include "client.h"
#include "libs/myteams/logging_client.h"

void code_114(const char *args)
{
    char **arg = get_return_args(args);

    for (int i = 0; arg[i]; i++) {
        client_print_teams(arg[i], arg[i + 1], arg[i + 2]);
        i += 2;
    }
}