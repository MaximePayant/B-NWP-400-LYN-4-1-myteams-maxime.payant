/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** object_emplace_primitive.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../jsnp_header.h"

jsnp_token_t *object_emplace_primitive_back(jsnp_value_t *u, const char *key, int value)
{
    jsnp_token_t *token = create_primitive(key, value);

    insert_token_back(u, token);
    return (token);
}

jsnp_token_t *object_emplace_primitive_front(jsnp_value_t *u, const char *key, int value)
{
    jsnp_token_t *token = create_primitive(key, value);

    insert_token_front(u, token);
    return (token);
}

jsnp_token_t *object_emplace_primitive_at(jsnp_value_t *u, const char *key, int value, unsigned index)
{
    jsnp_token_t *token = create_primitive(key, value);

    insert_token_at(u, token, index);
    return (token);
}