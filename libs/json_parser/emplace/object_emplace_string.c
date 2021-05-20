/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** object_emplace_string.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../utils/utils.h"
#include "../jsnp_header.h"

jsnp_token_t *object_emplace_string_back(jsnp_value_t *u, const char *key, const char *value)
{
    jsnp_token_t *token = create_string(key, value);

    insert_token_back(u, token);
    return (token);
}

jsnp_token_t *object_emplace_string_front(jsnp_value_t *u, const char *key, const char *value)
{
    jsnp_token_t *token = create_string(key, value);

    insert_token_front(u, token);
    return (token);
}

jsnp_token_t *object_emplace_string_at(jsnp_value_t *u, const char *key, const char *value, int index)
{
    jsnp_token_t *token = create_string(key, value);

    insert_token_at(u, token, index);
    return (token);
}