/*
** EPITECH PROJECT, 2021
** code_handler.c
** File description:
** code_handler.c
*/

#include <string.h>
#include "client.h"

const char *return_code[] = {"101", "102", "103", "104", "105", "106", "107",
"108", "109", "110", "111", "112", "113", "114","439", "440", "441", "442",
"443", "444", NULL};

void code_handler(char *code, char *args)
{
    void (*list_func[])(const char *) = {&code_101, &code_102, &code_103, &code_104, &code_105,
                                         &code_106, &code_107, &code_108,
                                         &code_109, &code_110, &code_111,
                                         &code_112, &code_113, &code_114,
                                         &code_439, &code_440, &code_441,
                                         &code_442, &code_443, &code_444,
                                         NULL};

    for (int i = 0; return_code[i]; i++) {
        if (strcmp(code, return_code[i]) == 0)
            list_func[i](args);
    }
    if (strcmp(code, "222") == 0)
        event_handler(args);
}