/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** take_string.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../jsnp_header.h"

char *take_string(const char *str, unsigned *ctr)
{
    char *result;
    int size = 0;

    *ctr += 1;
    while (str[*ctr + size] != '"')
        size += 1;
    result = malloc(sizeof(char) * (size + 1));
    if (!result)
        return (NULL);
    for (int i = 0; i < size; i += 1) {
        result[i] = str[*ctr];
        *ctr += 1;
    }
    result[size] = '\0';
    *ctr += 1;
    return (result);
}