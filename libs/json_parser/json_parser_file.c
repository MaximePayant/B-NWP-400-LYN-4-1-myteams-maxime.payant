/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** json_parser_split.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "jsnp_header.h"
#include "utils/utils.h"


static jsnp_t *split_object(const char *str);


jsnp_t *jsnp_parse_file(const char *filename)
{
    char *file = NULL;
    jsnp_t *jsnp = NULL;

    file = jsnp_read_file(filename);
    if (!file)
        return (NULL);
    jsnp = split_object(file);
    free(file);
    return (jsnp);
}

static jsnp_t *split_object(const char *str)
{
    unsigned count = count_value(str, ':');
    jsnp_t *jsnp = NULL;
    unsigned ctr = 0;
    unsigned brack_ctr = 0;

    jsnp = create_jsnp();
    if (!jsnp)
        return (NULL);
    while (str[ctr] && jsnp->value->count < count) {
        if (brack_ctr < 2 && str[ctr] == ':')
            insert_token_back(jsnp->value, take_token(str, &ctr));
        else
            ctr += 1;
    }
    return (jsnp);
}