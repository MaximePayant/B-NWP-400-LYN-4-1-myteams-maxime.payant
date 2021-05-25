/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** take_object.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "../jsnp_header.h"
#include "../utils/utils.h"

void take_object(jsnp_value_t *value, const char *str, unsigned *ctr)
{
    unsigned count = count_value(&str[*ctr], ':');
    unsigned brack_ctr = 1;

    value->type = JSNP_OBJECT;
    value->count = 0;
    LIST_INIT(&value->objects);

    *ctr += 1;
    while (str[*ctr] && value->count < count) {
        if (brack_ctr < 2 && str[*ctr] == ':')
            insert_token_back(value, take_token(str, ctr));
        brack_ctr += in_couple(str[*ctr]);
        if (brack_ctr < 2 && str[*ctr] == '}')
            continue;
        *ctr += 1;
    }
    *ctr += 1;
}