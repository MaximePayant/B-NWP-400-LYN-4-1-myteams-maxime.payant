/*
** EPITECH PROJECT, 2021
** get_return_tags.c
** File description:
** get_return_tags.c
*/

#include <stddef.h>
#include <string.h>
#include <malloc.h>

static char **add_value(char **return_args, int *index, char *value, char **arg)
{
    if (!return_args) {
        return_args = malloc(sizeof(char *));
        return_args[*index] = strdup(value);
        (*index)++;
        (*arg) += strlen(value) + 1;
    } else {
        return_args = reallocarray(return_args, *index + 1, sizeof(char *));
        return_args[*index] = strdup(value);
        (*index)++;
        (*arg) += strlen(value) + 1;
    }
    return (return_args);
}

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
        return_args = add_value(return_args, &index, value, &arg);
    } while (arg);
    return_args = reallocarray(return_args, index + 1, sizeof(char *));
    return_args[index] = NULL;
    free(save);
    return (return_args);
}