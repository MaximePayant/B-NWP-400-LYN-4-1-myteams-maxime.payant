/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** array_emplace_object.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../jsnp_header.h"

jsnp_value_t *array_emplace_object_back(jsnp_value_t *u)
{
    jsnp_value_t *v = malloc(sizeof(jsnp_value_t));

    if (!v)
        return (NULL);
    v->type = JSNP_OBJECT;
    v->count = 0;
    LIST_INIT(&v->objects);
    insert_value_back(u, v);
    return (v);
}

jsnp_value_t *array_emplace_object_front(jsnp_value_t *u)
{
    jsnp_value_t *v = malloc(sizeof(jsnp_value_t));

    if (!v)
        return (NULL);
    v->type = JSNP_OBJECT;
    v->count = 0;
    LIST_INIT(&v->objects);
    insert_value_front(u, v);
    return (v);
}

jsnp_value_t *array_emplace_object_at(jsnp_value_t *u, unsigned index)
{
    jsnp_value_t *v = malloc(sizeof(jsnp_value_t));

    if (!v)
        return (NULL);
    v->type = JSNP_OBJECT;
    v->count = 0;
    LIST_INIT(&v->objects);
    insert_value_at(u, v, index);
    return (v);
}