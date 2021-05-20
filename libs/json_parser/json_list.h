/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** json_list.h
*/

#ifndef __JSON_LIST_H__
#define __JSON_LIST_H__

#include "data_type.h"

jsnp_t *create_jsnp(void);
jsnp_token_t *create_primitive(const char *key, int primitive);
jsnp_token_t *create_string(const char *key, const char *str);
jsnp_token_t *create_array(const char *key);
jsnp_token_t *create_object(const char *key);

void insert_token_at(jsnp_value_t *u, jsnp_token_t *token, unsigned index);
void insert_token_front(jsnp_value_t *u, jsnp_token_t *token);
void insert_token_back(jsnp_value_t *u, jsnp_token_t *token);

void insert_value_at(jsnp_value_t *u, jsnp_value_t *value, unsigned index);
void insert_value_front(jsnp_value_t *u, jsnp_value_t *value);
void insert_value_back(jsnp_value_t *u, jsnp_value_t *value);

jsnp_token_t *object_emplace_primitive_back(jsnp_value_t *u, const char *key, int value);
jsnp_token_t *object_emplace_primitive_front(jsnp_value_t *u, const char *key, int value);
jsnp_token_t *object_emplace_primitive_at(jsnp_value_t *u, const char *key, int value, int index);
jsnp_value_t *array_emplace_primitive_back(jsnp_value_t *u, int value);
jsnp_value_t *array_emplace_primitive_front(jsnp_value_t *u, int value);
jsnp_value_t *array_emplace_primitive_at(jsnp_value_t *u, int value, int index);

jsnp_token_t *object_emplace_string_back(jsnp_value_t *u, const char *key, const char *value);
jsnp_token_t *object_emplace_string_front(jsnp_value_t *u, const char *key, const char *value);
jsnp_token_t *object_emplace_string_at(jsnp_value_t *u, const char *key, const char *value, int index);
jsnp_value_t *array_emplace_string_back(jsnp_value_t *u, const char *value);
jsnp_value_t *array_emplace_string_front(jsnp_value_t *u, const char *value);
jsnp_value_t *array_emplace_string_at(jsnp_value_t *u, const char *value, int index);

jsnp_token_t *object_emplace_array_front(jsnp_value_t *u, const char *key);
jsnp_token_t *object_emplace_array_back(jsnp_value_t *u, const char *key);
jsnp_token_t *object_emplace_array_at(jsnp_value_t *u, const char *key, int index);
jsnp_value_t *array_emplace_array_back(jsnp_value_t *u);
jsnp_value_t *array_emplace_array_front(jsnp_value_t *u);
jsnp_value_t *array_emplace_array_at(jsnp_value_t *u, int index);

jsnp_token_t *object_emplace_object_back(jsnp_value_t *u, const char *key);
jsnp_token_t *object_emplace_object_front(jsnp_value_t *u, const char *key);
jsnp_token_t *object_emplace_object_at(jsnp_value_t *u, const char *key, int index);
jsnp_value_t *array_emplace_object_back(jsnp_value_t *u);
jsnp_value_t *array_emplace_object_front(jsnp_value_t *u);
jsnp_value_t *array_emplace_object_at(jsnp_value_t *u, int index);

#endif // __JSON_LIST_H__