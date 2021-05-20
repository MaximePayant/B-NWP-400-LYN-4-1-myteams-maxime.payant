/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** str_cmp.c
*/

int str_cmp(const char *s1, const char *s2)
{
    if (!s1 && !s2)
        return (0);
    if (!s1)
        return (-1);
    if (!s2)
        return (1);
    for (int ctr = 0; s1[ctr] && s2[ctr]; ctr += 1)
        if (s1[ctr] != s2[ctr])
            return (s1[ctr] - s2[ctr]);
    return (0);
}