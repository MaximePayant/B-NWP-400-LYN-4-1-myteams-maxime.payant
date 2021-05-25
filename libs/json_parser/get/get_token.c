/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** get_token.c
*/

#include <unistd.h>

#include "../utils/utils.h"
#include "../jsnp_header.h"

jsnp_token_t *get_token(jsnp_value_t *value, const char *key)
{
    jsnp_token_t *it;

    if (value->type != JSNP_OBJECT)
        return (write(2, "Not an object\n", 14), NULL);
    it = value->objects.lh_first;
    for (; it != NULL; it = it->next.le_next)
        if (str_cmp(it->key, key) == 0)
            return (it);
    return (NULL);
}