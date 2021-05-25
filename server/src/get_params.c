/*
** EPITECH PROJECT, 2021
** get_return_tags.c
** File description:
** get_return_tags.c
*/

#include <stddef.h>
#include <string.h>
#include <malloc.h>

char **get_params(const char *args)
{
    char **return_args = NULL;
    char *save = strdup(args);
    char *arg = save;
    char *value = NULL;
    int index = 0;

    do {
        arg = strstr(arg + 1, "\"");
        if (!arg)
            continue;
        value = strdup(arg + 1);
        value = strtok(value, "\"");
        if (!return_args) {
            return_args = malloc(sizeof(char *));
            return_args[index] = strdup(value);
            index++;
            arg += strlen(value) + 1;
        } else {
            return_args = reallocarray(return_args, index + 1, sizeof(char *));
            return_args[index] = strdup(value);
            index++;
            arg += strlen(value) + 1;
        }
    } while (arg);
    return_args = reallocarray(return_args, index + 1, sizeof(char *));
    return_args[index] = NULL;
    free(save);
    return (return_args);
}