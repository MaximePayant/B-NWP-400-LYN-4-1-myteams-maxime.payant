/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** json_parser_write.c
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "jsnp_header.h"
#include "utils/utils.h"

static void write_token(jsnp_token_t *token, int fd);
static void write_value(jsnp_value_t *value, int fd);
static void write_array(jsnp_value_t *value, int fd);
static void write_objects(jsnp_value_t *value, int fd);

static unsigned key_tab_count(int off);
static unsigned val_tab_count(int off);

void write_jsnp(jsnp_t *jsnp, const char *filename)
{
    int fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);

    if (fd == -1)
        return;
    write(fd, "{\n", 2);
    for (jsnp_token_t *it = jsnp->value->objects.lh_first; it != NULL; it = it->next.le_next) {
        write_token(it, fd);
        if (it->next.le_next != NULL)
            write(fd, ",\n", 2);
    }
    write(fd, "\n}", 2);
    close(fd);
}

static void write_token(jsnp_token_t *token, int fd)
{
    key_tab_count(1);
    for (unsigned ctr = 0; ctr < key_tab_count(0); ctr += 1)
        write(fd, "  ", 2);
    write(fd, "\"", 1);
    write(fd, token->key, str_len(token->key));
    write(fd, "\": ", 3);
    write_value(token->value, fd);
    key_tab_count(-1);
}

static void write_number(int value, int fd)
{
    int size = snprintf(NULL, 0, "%d", value);
    char str[size];

    sprintf(str, "%i", value);
    write(fd, str, size);
}

static void write_value(jsnp_value_t *value, int fd)
{
    val_tab_count(1);
    switch (value->type) {
        case JSNP_PRIMITIVE:
            write_number(value->primitive, fd);
            break;
        case JSNP_STRING:
            write(fd, "\"", 1);
            write(fd, value->str, str_len(value->str));
            write(fd, "\"", 1);
            break;
        case JSNP_ARRAY:
            write_array(value, fd);
            break;
        case JSNP_OBJECT:
            write_objects(value, fd);
            break;
    }
    val_tab_count(-1);
}

static void write_array(jsnp_value_t *value, int fd)
{
    val_tab_count(1);
    write(fd, "[\n", 2);
    for (jsnp_value_t *it = value->array.lh_first;
    it != NULL; it = it->next.le_next) {
        for (unsigned ctr = 0; ctr < val_tab_count(0) - 1; ctr += 1)
            write(fd, "  ", 2);
        write_value(it, fd);
        if (it->next.le_next != NULL)
            write(fd, ",\n", 2);
    }
    write(fd, "\n", 1);
    for (unsigned ctr = 0; ctr < key_tab_count(0); ctr += 1)
        write(fd, "  ", 2);
    write(fd, "]", 1);
    val_tab_count(-1);
}

static void write_objects(jsnp_value_t *value, int fd)
{
    for (unsigned ctr = 0; ctr < key_tab_count(0); ctr += 1)
        write(fd, "  ", 2);
    write(fd, "{\n", 2);
    key_tab_count(1);
    for (jsnp_token_t *it = value->objects.lh_first;
    it != NULL; it = it->next.le_next) {
        write_token(it, fd);
        if (it->next.le_next != NULL)
            write(fd, ",\n", 2);
    }
    write(fd, "\n", 1);
    for (unsigned ctr = 0; ctr < key_tab_count(0); ctr += 1)
        write(fd, "  ", 2);
    write(fd, "}", 1);
    key_tab_count(-1);
}

static unsigned key_tab_count(int off)
{
    static unsigned key_tab_count = 0;

    key_tab_count += off;
    return (key_tab_count);
}

static unsigned val_tab_count(int off)
{
    static unsigned val_tab_count = 0;

    val_tab_count += off;
    return (val_tab_count);
}