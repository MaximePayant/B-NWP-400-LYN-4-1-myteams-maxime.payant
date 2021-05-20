/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** in_couple.c
*/

#include <stdbool.h>

int in_couple(char c)
{
    static bool in_quote = false;

    switch (c) {
        case '"':
            in_quote = !in_quote;
            return (in_quote ? 1 : -1);
        case '{':
        case '[':
            return (!in_quote ? 1 : 0);
        case '}':
        case ']':
            return (!in_quote ? -1 : 0);
    }
    return (0);
}