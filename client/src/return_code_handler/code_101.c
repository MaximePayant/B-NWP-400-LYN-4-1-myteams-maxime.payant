/*
** EPITECH PROJECT, 2021
** code_101.c
** File description:
** code_101.c
*/

#include <string.h>
#include <malloc.h>

void code_101(const char *args)
{
    char *uuid = strstr(args, "{");
    char *name = strdup(uuid);
    char *save = name;

    name = strstr(name + 1, "{");
    uuid = strtok(uuid, "}");
    name = strtok(name, "}");
    free(save);
}