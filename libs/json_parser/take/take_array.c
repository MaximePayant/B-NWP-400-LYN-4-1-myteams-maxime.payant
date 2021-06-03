/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** take_array.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../jsnp_header.h"
#include "../utils/utils.h"

void take_array(jsnp_value_t *value, const char *str, unsigned *ctr)
{
    unsigned count = count_value(&str[*ctr], ',') + 1;
    unsigned brack_ctr = 1;

    if (str[*ctr + 1] == ']')
        count -= 1;
    value->type = JSNP_ARRAY;
    value->count = 0;
    LIST_INIT(&value->array);

    *ctr += 1;
    while (str[*ctr] && value->count < count) {
        if (brack_ctr < 2)
            insert_value_back(value, take_value(str, ctr));
        brack_ctr += in_couple(str[*ctr]);
        if (brack_ctr < 2 && str[*ctr] == ']')
            continue;
        *ctr += 1;
    }
    *ctr += 1;
}