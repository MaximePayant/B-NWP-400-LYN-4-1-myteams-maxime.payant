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
    int nbr;

    strtok(args, "{");
    nbr = atoi(strtok(NULL, "}"));
    for (int i = 0; i != nbr; i++) {
        client_private_message_print_messages(strtok(NULL, "}")+3, string_to_time(strtok(NULL, "}")+3), strtok(NULL, "}")+3);
    }
}