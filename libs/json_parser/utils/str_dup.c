/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** str_dup.c
*/

#include <stdlib.h>
#include "utils.h"

char *str_dup(const char *str)
{
    int size = str_len(str);
    char *result = NULL;

    if (!size)
        return (NULL);
    result = malloc(sizeof(char) * (size + 1));
    for (int ctr = 0; ctr < size; ctr += 1)
        result[ctr] = str[ctr];
    result[size] = '\0';
    return (result);
}