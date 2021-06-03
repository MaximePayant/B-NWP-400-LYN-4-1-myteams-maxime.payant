/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** read_file.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "utils/utils.h"

static char *read_file(const char *filename);
static bool verif_extension(const char *str);
static char *clean_file(char *str);

char *jsnp_read_file(const char *filename)
{
    char *file = NULL;

    if (!verif_extension(filename))
        return (NULL);
    file = read_file(filename);
    if (!file)
        return (NULL);
    file = clean_file(file);
    if (!file)
        return (NULL);
    return (file);
}

static char *read_file(const char *filename)
{
    int error = 0;
    struct stat st;
    int fd = 0;
    char *buffer = NULL;

    error = stat(filename, &st);
    if (error == -1)
        return (NULL);
    buffer = malloc(sizeof(char) * (st.st_size + 1));
    if (buffer == NULL)
        return (NULL);
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (NULL);
    error = read(fd, buffer, st.st_size);
    if (error == -1)
        return (close(fd), NULL);
    buffer[st.st_size] = '\0';
    close(fd);
    return (buffer);
}

static bool verif_extension(const char *str)
{
    int size = str_len(str);

    if (str_cmp(&str[size - 5], ".json"))
        return (false);
    return (true);
}

static char *clean_file(char *str)
{
    char *file = malloc(sizeof(char) * (str_len(str) + 1));
    char *result = NULL;
    int fctr = 0;
    bool in_quote = false;

    if (!file)
        return (NULL);
    for (int ctr = 0; str[ctr]; ctr += 1) {
        if (!in_quote && str_contain(str[ctr], " \n\t"))
            continue;
        if (str[ctr] == '\"' && ctr > 0 && str[ctr - 1] != '\\')
            in_quote = !in_quote;
        file[fctr] = str[ctr];
        fctr += 1;
    }
    file[fctr] = '\0';
    result = str_dup(file);
    free(str);
    free(file);
    return (result);
}