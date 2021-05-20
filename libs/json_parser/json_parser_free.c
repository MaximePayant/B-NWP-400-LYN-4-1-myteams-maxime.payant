/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** json_parser_free.c
*/

#include <stdlib.h>

#include "jsnp_header.h"

void free_token(jsnp_token_t *token);
void free_value(jsnp_value_t *value);
static void free_array(jsnp_value_t *value);
static void free_objects(jsnp_value_t *value);

void free_jsnp(jsnp_t *jsnp)
{
    jsnp_token_t *next;

    for (jsnp_token_t *it = jsnp->value->objects.lh_first;
    it != NULL; it = next) {
        next = it->next.le_next;
        free_token(it);
    }
    free(jsnp->value);
    free(jsnp);
}

void free_token(jsnp_token_t *token)
{
    free(token->key);
    free_value(token->value);
    free(token);
}

void free_value(jsnp_value_t *value)
{
    switch (value->type) {
        case JSNP_PRIMITIVE:
            break;
        case JSNP_STRING:
            free(value->str);
            break;
        case JSNP_ARRAY:
            free_array(value);
            break;
        case JSNP_OBJECT:
            free_objects(value);
            break;
    }
    free(value);
}

static void free_array(jsnp_value_t *value)
{
    jsnp_value_t *next;

    for (jsnp_value_t *it = value->array.lh_first; it != NULL; it = next) {
        next = it->next.le_next;
        free_value(it);
    }
}

static void free_objects(jsnp_value_t *value)
{
    jsnp_token_t *next;

    for (jsnp_token_t *it = value->objects.lh_first; it != NULL; it = next) {
        next = it->next.le_next;
        free_token(it);
    }
}