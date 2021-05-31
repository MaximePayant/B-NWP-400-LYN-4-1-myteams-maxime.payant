/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** time_t_converter.c
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int next_number(char *str, int ctr)
{
    if (str)
        while (str[ctr] && '0' <= str[ctr] && str[ctr] <= '9')
            ctr += 1;
    ctr += 1;
    return (ctr);
}

char *time_to_string(time_t time)
{
    struct tm *tm = localtime(&time);
    char str[50];
    int i = sprintf(str, "%i:%i:%i:%i:%i:%i:%i:%i:%i", tm->tm_sec, tm->tm_min,
    tm->tm_hour, tm->tm_mday, tm->tm_mon, tm->tm_year, tm->tm_wday,
    tm->tm_yday, tm->tm_isdst);
    char *result;

    str[i] = '\0';
    result = strdup(str);
    return (result);
}

time_t string_to_time(char *string)
{
    time_t time_st;
    struct tm *tm = malloc(sizeof(struct tm));
    int ctr = 0;

    tm->tm_sec = atoi(string);
    ctr = next_number(string, ctr);
    tm->tm_min = atoi(&string[ctr]);
    ctr = next_number(string, ctr);
    tm->tm_hour = atoi(&string[ctr]);
    ctr = next_number(string, ctr);
    tm->tm_mday = atoi(&string[ctr]);
    ctr = next_number(string, ctr);
    tm->tm_mon = atoi(&string[ctr]);
    ctr = next_number(string, ctr);
    tm->tm_year = atoi(&string[ctr]);
    ctr = next_number(string, ctr);
    tm->tm_wday = atoi(&string[ctr]);
    ctr = next_number(string, ctr);
    tm->tm_yday = atoi(&string[ctr]);
    tm->tm_isdst = atoi(&string[next_number(string, ctr)]);
    time_st = mktime(tm);
    return (free(tm), time_st);
}