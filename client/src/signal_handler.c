/*
** EPITECH PROJECT, 2021
** signal_handler.c
** File description:
** signal_handler.c
*/

#include <stdlib.h>
#include "client.h"

void signal_handler(int signum)
{
    (void) signum;
    send_command(get_client(NULL), "/logout");
    exit(0);
}

