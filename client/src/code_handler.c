/*
** EPITECH PROJECT, 2021
** code_handler.c
** File description:
** code_handler.c
*/

#include <string.h>
#include <stdio.h>
#include "client.h"

const char *return_code[] = {"101", "102", "103", "104", "105", "106", "107",
                             "108", "109", "110", "111", "112", "113", "114",
                             NULL};

void code_handler(char *code, char *args)
{
    void (*list_func[])(const char *) = {&code_101, &code_102, NULL, NULL, NULL,
                                         &code_106, &code_107, &code_108, &code_109, NULL,
                                         &code_111, &code_112, NULL};

    if (strstr(code, "4") == code) {
        printf("%s", args);
        return;
    }
    for (int i = 0; return_code[i]; i++) {
        if (strcmp(code, return_code[i]) == 0)
            list_func[i](args);
    }
}