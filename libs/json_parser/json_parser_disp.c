/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** json_parser_disp.c
*/

#include <stdio.h>

#include "jsnp_header.h"


void disp_token(jsnp_token_t *token);
void disp_value(jsnp_value_t *value);
static void disp(unsigned count, const char *str);
static unsigned key_tab_count(int off);
static unsigned val_tab_count(int off);


void disp_jsnp(jsnp_t *jsnp)
{
    for (jsnp_token_t *it = jsnp->value->objects.lh_first; it != NULL; it = it->next.le_next)
        disp_token(it);
}

static void disp_value_type(jsnp_value_t *value)
{
    val_tab_count(1);
    disp(val_tab_count(0), "");
    switch (value->type) {
        case JSNP_PRIMITIVE:
            printf("Type: Primitive\n");
            break;
        case JSNP_STRING:
            printf("Type: String\n");
            break;
        case JSNP_ARRAY:
            printf("Type: Array\n");
            break;
        case JSNP_OBJECT:
            printf("Type: Object\n");
            break;
    }
    val_tab_count(-1);
}

void disp_token(jsnp_token_t *token)
{
    key_tab_count(1);
    for (unsigned ctr = 0; ctr < key_tab_count(0) - 1; ctr += 1)
        printf("  ");
    printf("Key: %s\n", token->key);
    disp_value_type(token->value);
    disp_value(token->value);
    printf("\n");
    key_tab_count(-1);
}

void disp_value(jsnp_value_t *value)
{
    val_tab_count(1);
    disp(val_tab_count(0), "");
    switch (value->type) {
        case JSNP_PRIMITIVE:
            printf("Value: %i\n", value->primitive);
            break;
        case JSNP_STRING:
            printf("Value: %s\n", value->str);
            break;
        case JSNP_ARRAY:
            printf("[\n");
            key_tab_count(1);
            for (jsnp_value_t *it = value->array.lh_first; it != NULL; it = it->next.le_next)
                disp_value(it);
            key_tab_count(-1);
            disp(val_tab_count(0), "]\n");
            break;
        case JSNP_OBJECT:
            printf("{\n");
            for (jsnp_token_t *it = value->objects.lh_first; it != NULL; it = it->next.le_next)
                disp_token(it);
            disp(val_tab_count(0), "}\n");
            break;
    }
    val_tab_count(-1);
}

static void disp(unsigned count, const char *str)
{
    for (unsigned ctr = 0; ctr < count - 1; ctr += 1)
        printf("  ");
    printf("%s", str);
}

static unsigned key_tab_count(int off)
{
    static unsigned key_tab_count = 0;

    key_tab_count += off;
    return (key_tab_count);
}

static unsigned val_tab_count(int off)
{
    static unsigned val_tab_count = 0;

    val_tab_count += off;
    return (val_tab_count);
}