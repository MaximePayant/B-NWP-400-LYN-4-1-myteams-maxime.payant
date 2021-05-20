/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** utils.hpp
*/

#ifndef __JSNP_UTILS_H__
#define __JSNP_UTILS_H__

#include <stdbool.h>

unsigned count_value(const char *str, char c);
int in_couple(char c);
int str_cmp(const char *s1, const char *s2);
bool str_contain(char c, const char *str);
char *str_dup(const char *str);
unsigned str_len(const char *str);

#endif // __JSNP_UTILS_H__