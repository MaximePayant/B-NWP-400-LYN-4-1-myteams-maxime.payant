/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** create_array.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../utils/utils.h"
#include "../data_type.h"

jsnp_token_t *create_array(const char *key)
{
    jsnp_token_t *token = malloc(sizeof(jsnp_token_t));

    if (!token)
        return (perror("malloc"), NULL);
    token->key = str_dup(key);
    token->value = malloc(sizeof(jsnp_value_t));
    if (!token->value)
        return (perror("malloc"), NULL);
    token->value->type = JSNP_ARRAY;
    token->value->count = 0;
    LIST_INIT(&token->value->array);
    return (token);
}