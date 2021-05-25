/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** str_len.c
*/

unsigned str_len(const char *str)
{
    int len = 0;

    if (str)
        while (str[len])
            len += 1;
    return (len);
}