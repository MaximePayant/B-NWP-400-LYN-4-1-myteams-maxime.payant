/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** take_value.c
*/

#include <stdlib.h>

#include "../jsnp_header.h"

jsnp_value_t *take_value(const char *str, unsigned *ctr)
{
    jsnp_value_t *value = malloc(sizeof(jsnp_value_t));

    if (str[*ctr] == ':')
        *ctr += 1;
    switch (str[*ctr]) {
        case '"':
            value->type = JSNP_STRING;
            value->str = take_string(str, ctr);
            break;
        case '[':
            take_array(value, str, ctr);
            break;
        case '{':
            take_object(value, str, ctr);
            break;
        default:
            value->type = JSNP_PRIMITIVE;
            value->primitive = take_primitive(str, ctr);
            break;
    }
    return (value);
}