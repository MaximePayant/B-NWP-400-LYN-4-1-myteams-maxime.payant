/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** get_value.c
*/

#include <unistd.h>

#include "../jsnp_header.h"

jsnp_value_t *get_value(jsnp_value_t *value, unsigned index)
{
    jsnp_value_t *it;

    if (value->type != JSNP_ARRAY)
        return (write(2, "Not an object\n", 14), NULL);
    if (index > value->count)
        return (write(2, "Out of range\n", 13), NULL);
    it = value->array.lh_first;
    for (unsigned ctr = 1; ctr != index && it != NULL; ctr += 1)
        it = it->next.le_next;
    return (it);
}