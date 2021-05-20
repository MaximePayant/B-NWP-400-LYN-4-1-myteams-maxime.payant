/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** take_primitive.c
*/

#include <stdlib.h>

#include "../jsnp_header.h"

static int take_primitive_bis(const char *str, unsigned *ctr);

int take_primitive(const char *str, unsigned *ctr)
{
    int result;

    result = 0;
    switch (str[*ctr]) {
        case 't':
            result = 1;
            break;
        case 'f':
        case 'n':
            result = 0;
            break;
        default:
            result = take_primitive_bis(str, ctr);
            break;
    }
    while (str[*ctr] != ',' && str[*ctr] != ']' && str[*ctr] != '}')
        *ctr += 1;
    *ctr += 1;
    return (result);
}

static int take_primitive_bis(const char *str, unsigned *ctr)
{
    int value = 0;

    switch (str[*ctr]) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '-':
            value = atoi(&str[*ctr]);
            break;
    }
    return (value);
}