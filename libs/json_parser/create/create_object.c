/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** create_object.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../utils/utils.h"
#include "../data_type.h"

jsnp_token_t *create_object(const char *key)
{
    jsnp_token_t *token = malloc(sizeof(jsnp_token_t));

    if (!token)
        return (NULL);
    token->key = str_dup(key);
    token->value = malloc(sizeof(jsnp_value_t));
    if (!token->value)
        return (NULL);
    token->value->type = JSNP_OBJECT;
    token->value->count = 0;
    LIST_INIT(&token->value->objects);
    return (token);
}