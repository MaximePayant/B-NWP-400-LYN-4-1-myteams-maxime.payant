/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** array_emplace_string.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../utils/utils.h"
#include "../jsnp_header.h"

jsnp_value_t *array_emplace_string_back(jsnp_value_t *u, const char *value)
{
    jsnp_value_t *v = malloc(sizeof(jsnp_value_t));

    if (!v)
        return (perror("malloc"), NULL);
    v->type = JSNP_STRING;
    v->count = 0;
    v->str = str_dup(value);
    insert_value_back(u, v);
    return (v);
}

jsnp_value_t *array_emplace_string_front(jsnp_value_t *u, const char *value)
{
    jsnp_value_t *v = malloc(sizeof(jsnp_value_t));

    if (!v)
        return (perror("malloc"), NULL);
    v->type = JSNP_STRING;
    v->count = 0;
    v->str = str_dup(value);
    insert_value_front(u, v);
    return (v);
}

jsnp_value_t *array_emplace_string_at(jsnp_value_t *u, const char *value, unsigned index)
{
    jsnp_value_t *v = malloc(sizeof(jsnp_value_t));

    if (!v)
        return (perror("malloc"), NULL);
    v->type = JSNP_STRING;
    v->count = 0;
    v->str = str_dup(value);
    insert_value_at(u, v, index);
    return (v);
}