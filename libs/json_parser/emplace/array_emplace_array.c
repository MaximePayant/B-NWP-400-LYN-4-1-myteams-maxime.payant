/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** array_emplace_array.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../utils/utils.h"
#include "../jsnp_header.h"

jsnp_value_t *array_emplace_array_back(jsnp_value_t *u)
{
    jsnp_value_t *v = malloc(sizeof(jsnp_value_t));

    if (!v)
        return (perror("malloc"), NULL);
    v->type = JSNP_ARRAY;
    v->count = 0;
    LIST_INIT(&v->array);
    insert_value_back(u, v);
    return (v);
}

jsnp_value_t *array_emplace_array_front(jsnp_value_t *u)
{
    jsnp_value_t *v = malloc(sizeof(jsnp_value_t));

    if (!v)
        return (perror("malloc"), NULL);
    v->type = JSNP_ARRAY;
    v->count = 0;
    LIST_INIT(&v->array);
    insert_value_front(u, v);
    return (v);
}

jsnp_value_t *array_emplace_array_at(jsnp_value_t *u, unsigned index)
{
    jsnp_value_t *v = malloc(sizeof(jsnp_value_t));

    if (!v)
        return (perror("malloc"), NULL);
    v->type = JSNP_ARRAY;
    v->count = 0;
    LIST_INIT(&v->array);
    insert_value_at(u, v, index);
    return (v);
}