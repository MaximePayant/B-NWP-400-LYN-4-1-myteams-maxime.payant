/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** insert_token.c
*/

#include <stdio.h>

#include "../data_type.h"

void insert_token_at(jsnp_value_t *value, jsnp_token_t *token, unsigned index)
{
    jsnp_token_t *it = value->objects.lh_first;

    value->count += 1;
    if (index == 1) {
        LIST_INSERT_HEAD(&value->objects, token, next);
        return;
    } else if (index > value->count) {
        printf("Try to insert out of range.\n");
        return;
    }
    for (unsigned ctr = 1; ctr < index - 1 && it != NULL; ctr += 1)
        it = it->next.le_next;
    LIST_INSERT_AFTER(it, token, next);
}

void insert_token_front(jsnp_value_t *value, jsnp_token_t *token)
{
    value->count += 1;
    LIST_INSERT_HEAD(&value->objects, token, next);
}

void insert_token_back(jsnp_value_t *value, jsnp_token_t *token)
{
    if (value->count == 0)
        insert_token_front(value, token);
    else
        insert_token_at(value, token, value->count + 1);
}