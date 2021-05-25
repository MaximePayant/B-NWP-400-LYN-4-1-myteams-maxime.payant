/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** count_value.c
*/

#include "utils.h"

unsigned count_value(const char *str, char c)
{
    unsigned count = 0;
    unsigned brack_ctr = 1;

    if (str)
        for (int ctr = 1; brack_ctr && str[ctr]; ctr += 1) {
            if (brack_ctr < 2 && str[ctr] == c)
                count += 1;
            brack_ctr += in_couple(str[ctr]);
        }
    return (count);
}