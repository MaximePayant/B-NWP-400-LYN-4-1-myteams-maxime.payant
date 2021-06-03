/*
** EPITECH PROJECT, 2021
** signal_handler.c
** File description:
** signal_handler.c
*/

#include <stdlib.h>
#include "server.h"

void signalHandler(int signum)
{
    (void)signum;
    end = 1;
}

