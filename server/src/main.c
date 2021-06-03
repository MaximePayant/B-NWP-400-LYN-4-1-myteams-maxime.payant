/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** main.cpp
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "server.h"
#include "libs/json_parser/json_parser.h"

int help_output(void)
{
    printf("USAGE: ./myteams_server port\n\t");
    printf("port  is the port number on which the server"
    " socket listens.\n");
    return (0);
}

int main(int ac, char **av)
{
    server_t *server = NULL;

    if (ac != 2)
        return (84);
    if (strcmp(av[1], "-help") == 0)
        return (help_output());
    server = load(atoi(av[1]));
    get_server(server);
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    if (init_server(server) == 1) {
        printf("[SERVER] Cannot initialize the server\n");
        free((server));
        return (84);
    }
    server_core(server);
    return (0);
}