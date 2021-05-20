/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** str_contain.c
*/

#include <stdbool.h>

bool str_contain(char c, const char *str)
{
    if (str)
        for (int ctr = 0; str[ctr]; ctr += 1)
            if (str[ctr] == c)
                return (true);
    return (false);
}