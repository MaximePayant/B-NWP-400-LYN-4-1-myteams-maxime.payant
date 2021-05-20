/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** take_token.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../jsnp_header.h"

static char *take_key(const char *str, unsigned ctr);

jsnp_token_t *take_token(const char *str, unsigned *ctr)
{
    jsnp_token_t *token = malloc(sizeof(jsnp_token_t));

    if (!token)
        return (perror("malloc"), NULL);

    token->key = take_key(str, *ctr);
    token->value = take_value(str, ctr);
    return (token);
}

static char *take_key(const char *str, unsigned ctr)
{
    int size = 0;
    char *result = NULL;

    ctr -= 2;
    while (str[ctr - size] != '"')
        size += 1;
    result = malloc(sizeof(char) * (size + 1));
    if (!result)
        return (perror("malloc"), NULL);
    for (int i = 0; i < size; i += 1)
        result[size - (1 + i)] = str[ctr - i];
    result[size] = '\0';
    return (result);
}