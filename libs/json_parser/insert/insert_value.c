/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** insert_value.c
*/

#include <stdio.h>

#include "../data_type.h"

void insert_value_at(jsnp_value_t *u, jsnp_value_t *value, unsigned index)
{
    jsnp_value_t *it = u->array.lh_first;

    u->count += 1;
    if (index == 1) {
        LIST_INSERT_HEAD(&u->array, value, next);
        return;
    } else if (index > u->count) {
        printf("Try to insert out of range.\n");
        return;
    }
    for (unsigned ctr = 1; ctr < index - 1 && it != NULL; ctr += 1)
        it = it->next.le_next;
    LIST_INSERT_AFTER(it, value, next);
}

void insert_value_front(jsnp_value_t *u, jsnp_value_t *value)
{
    u->count += 1;
    LIST_INSERT_HEAD(&u->array, value, next);
}

void insert_value_back(jsnp_value_t *u, jsnp_value_t *value)
{
    if (u->count == 0)
        insert_value_front(u, value);
    else
        insert_value_at(u, value, u->count + 1);
}