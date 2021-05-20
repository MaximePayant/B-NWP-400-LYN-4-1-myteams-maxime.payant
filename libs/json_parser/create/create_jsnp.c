/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** create_jsnp.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../data_type.h"

jsnp_t *create_jsnp(void)
{
    jsnp_t *jsnp = malloc(sizeof(jsnp_t));

    if (!jsnp)
        return (perror("malloc"), NULL);
    jsnp->value = malloc(sizeof(jsnp_value_t));
    if (!jsnp->value)
        return (perror("malloc"), NULL);
    jsnp->value->count = 0;
    jsnp->value->type = JSNP_OBJECT;
    LIST_INIT(&jsnp->value->objects);
    return (jsnp);
}