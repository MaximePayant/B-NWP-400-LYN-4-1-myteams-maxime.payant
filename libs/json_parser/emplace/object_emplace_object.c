/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** object_emplace_object.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../jsnp_header.h"

jsnp_token_t *object_emplace_object_back(jsnp_value_t *u, const char *key)
{
    jsnp_token_t *token = create_object(key);

    insert_token_back(u, token);
    return (token);
}

jsnp_token_t *object_emplace_object_front(jsnp_value_t *u, const char *key)
{
    jsnp_token_t *token = create_object(key);

    insert_token_front(u, token);
    return (token);
}

jsnp_token_t *object_emplace_object_at(jsnp_value_t *u, const char *key, int index)
{
    jsnp_token_t *token = create_object(key);

    insert_token_at(u, token, index);
    return (token);
}