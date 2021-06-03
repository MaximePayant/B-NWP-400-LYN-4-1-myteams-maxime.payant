/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** create_primitive.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../utils/utils.h"
#include "../data_type.h"

jsnp_token_t *create_primitive(const char *key, int primitive)
{
    jsnp_token_t *token = malloc(sizeof(jsnp_token_t));

    if (!token)
        return (NULL);
    token->key = str_dup(key);
    token->value = malloc(sizeof(jsnp_value_t));
    if (!token->value)
        return (NULL);
    token->value->type = JSNP_PRIMITIVE;
    token->value->count = 1;
    token->value->primitive = primitive;
    return (token);
}