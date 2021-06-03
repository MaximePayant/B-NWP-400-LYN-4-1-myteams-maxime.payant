/*
** EPITECH PROJECT, 2021
** code_111.c
** File description:
** code_111.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include "libs/myteams/logging_client.h"

void code_104(const char *args)
{
    char **list_args = get_return_args(args);

    for (int i = 0; list_args[i]; i++) {
        client_print_users(list_args[i], list_args[i + 1], atoi(list_args[i + 2]));
        i += 2;
    }
}