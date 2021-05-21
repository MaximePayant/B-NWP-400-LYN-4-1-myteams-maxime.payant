/*
** EPITECH PROJECT, 2021
** args.cpp
** File description:
** args.cpp
*/

#include <string.h>

char *get_args(const char *command)
{
    int space = -1;
    char *args = NULL;

    for (int i = 0; command[i] != '\0'; i++)
        if (command[i] == ' ') {
            space = i + 1;
            break;
        }
    if (space != -1)
        args = strdup(command + space);
    return (args);
}
