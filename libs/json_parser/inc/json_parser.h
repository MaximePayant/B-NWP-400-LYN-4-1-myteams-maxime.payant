/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** json_parser.h
*/

#ifndef __JSON_PARSER_H__
#define __JSON_PARSER_H__

#include "json_list.h"

jsnp_t *jsnp_parse_file(const char *filename);

void disp_jsnp(jsnp_t *jsnp);
void disp_token(jsnp_token_t *token);
void disp_value(jsnp_value_t value);

void write_jsnp(jsnp_t *jsnp, const char *filename);

void free_jsnp(jsnp_t *jsnp);
void free_token(jsnp_token_t *token);
void free_value(jsnp_value_t *value);

#endif // __JSON_PARSER_H__