/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** jsnp_header.h
*/

#ifndef __JSNP_HEADER_H__
#define __JSNP_HEADER_H__

#include "json_list.h"

char *jsnp_read_file(const char *filename);

jsnp_token_t *take_token(const char *str, unsigned *ctr);
jsnp_value_t *take_value(const char *str, unsigned *ctr);

int take_primitive(const char *str, unsigned *ctr);
char *take_string(const char *str, unsigned *ctr);
void take_array(jsnp_value_t *value, const char *str, unsigned *ctr);
void take_object(jsnp_value_t *value, const char *str, unsigned *ctr);

#endif // __JSNP_HEADER_H__