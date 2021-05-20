/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** create_string.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../utils/utils.h"
#include "../data_type.h"

jsnp_token_t *create_string(const char *key, const char *str)
{
    jsnp_token_t *token = malloc(sizeof(jsnp_token_t));

    if (!token)
        return (perror("malloc"), NULL);
    token->key = str_dup(key);
    token->value = malloc(sizeof(jsnp_value_t));
    if (!token->value)
        return (perror("malloc"), NULL);
    token->value->type = JSNP_STRING;
    token->value->count = 1;
    token->value->str = str_dup(str);
    return (token);
}