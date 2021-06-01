/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** main.cpp
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"

int help_output(void)
{
    printf("USAGE: ./myteams_server port\n\t");
    printf("port  is the port number on which the server socket listens.\n");
    return (0);
}

server_t *init_struct(char **av)
{
    server_t *new_server = malloc(sizeof(server_t));

    new_server->sock = (struct sockaddr_in){ 0 };
    new_server->sock_size = sizeof(new_server->sock);
    new_server->port = atoi(av[1]);
    new_server->client = NULL;
    new_server->server_socket = -1;
    new_server->teams = NULL;
    return (new_server);
}

int main(int ac, char **av)
{
    server_t *server = NULL;

    if (ac != 2)
        return (84);
    if (strcmp(av[1], "-help") == 0)
        return (help_output());
    server = init_struct(av);
    get_server(server);
    if (init_server(server) == 1) {
        printf("[SERVER] Cannot initialize the server\n");
        free((server));
        return (84);
    }
    server_core(server);
    return (0);
}