/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** array_emplace_primitive.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../jsnp_header.h"

jsnp_value_t *array_emplace_primitive_back(jsnp_value_t *u, int value)
{
    jsnp_value_t *v = malloc(sizeof(jsnp_value_t));

    if (!v)
        return (perror("malloc"), NULL);
    v->type = JSNP_PRIMITIVE;
    v->count = 0;
    v->primitive = value;
    insert_value_back(u, v);
    return (v);
}

jsnp_value_t *array_emplace_primitive_front(jsnp_value_t *u, int value)
{
    jsnp_value_t *v = malloc(sizeof(jsnp_value_t));

    if (!v)
        return (perror("malloc"), NULL);
    v->type = JSNP_PRIMITIVE;
    v->count = 0;
    v->primitive = value;
    insert_value_front(u, v);
    return (v);
}

jsnp_value_t *array_emplace_primitive_at(jsnp_value_t *u, int value, int index)
{
    jsnp_value_t *v = malloc(sizeof(jsnp_value_t));

    if (!v)
        return (perror("malloc"), NULL);
    v->type = JSNP_PRIMITIVE;
    v->count = 0;
    v->primitive = value;
    insert_value_at(u, v, index);
    return (v);
}