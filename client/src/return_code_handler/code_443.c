/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** code_408.c
*/

#include "client.h"
#include "libs/myteams/logging_client.h"

void code_443(const char *args)
{
    char **arg = get_return_args(args);

    client_error_unknown_thread(arg[0]);
}