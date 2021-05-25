/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** data_type.h
*/

#ifndef __JSON_PARSER_DATA_TYPE_H__
#define __JSON_PARSER_DATA_TYPE_H__

typedef enum json_parser_type_e
{
    JSNP_PRIMITIVE,
    JSNP_STRING,
    JSNP_ARRAY,
    JSNP_OBJECT
} jsnp_type_e;

typedef union  json_parser_value_u jsnp_value_u;
typedef struct json_parser_value_s jsnp_value_t;
typedef struct json_parser_token_s jsnp_token_t;
typedef struct json_parser_s       jsnp_t;

#include <stddef.h>
#include <sys/queue.h>
#include <stdbool.h>

struct json_parser_value_s
{
    jsnp_type_e type;
    unsigned count;
    union
    {
        int primitive;
        char *str;
        LIST_HEAD(value_list, json_parser_value_s) array;
        LIST_HEAD(token_list, json_parser_token_s) objects;
    };

    LIST_ENTRY(json_parser_value_s) next;
};

struct json_parser_token_s
{
    char *key;
    jsnp_value_t *value;

    LIST_ENTRY(json_parser_token_s) next;
};

struct json_parser_s
{
    jsnp_value_t *value;
};

#endif // __JSON_PARSER_DATA_TYPE_H__