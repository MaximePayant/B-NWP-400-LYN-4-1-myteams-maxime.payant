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

void code_107(const char *args)
{
    char **list_args = get_return_args(args);

    for (int i = 0; list_args[i]; i++) {
        client_private_message_print_messages(list_args[i],
        string_to_time(list_args[i + 1]),
        list_args[i + 2]);
        i += 2;
    }
}