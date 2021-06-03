/*
** EPITECH PROJECT, 2021
** man.c
** File description:
** man.c
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include "client.h"

client_t *get_client(client_t *client)
{
    static client_t *real_client = NULL;

    if (client)
        real_client = client;
    return (real_client);
}

int help_output(void)
{
    printf("USAGE: ./myteams_cli ip port\n\t");
    printf("ip\tis the server ip address on which"
    " the server socket listens\n");
    printf("\tport\tis the port number on which"
    " the server socket listens.\n");
    return (0);
}

client_t *init_struct(char **av)
{
    client_t *new_client = malloc(sizeof(client_t));

    new_client->ip = av[1];
    new_client->port = av[2];
    new_client->exit = 0;
    new_client->socket = socket(AF_INET, SOCK_STREAM, 0);
    new_client->sock = (struct sockaddr_in){ 0 };
    new_client->sock.sin_port = htons(atoi(new_client->port));
    new_client->sock.sin_addr.s_addr = inet_addr(new_client->ip);
    new_client->sock.sin_family = AF_INET;
    new_client->file = fdopen(new_client->socket, "rw");
    return (new_client);
}

void destroy_client(client_t *client)
{
    fclose(client->file);
    close(client->socket);
    free(client);
}

int main(int ac, char **av)
{
    client_t *client = NULL;

    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return (help_output());
    if (ac != 3)
        return (84);
    client = init_struct(av);
    get_client(client);
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    if (connect(client->socket, (struct sockaddr *) &client->sock,
    sizeof(client->sock)) == -1)
        printf("Connection refused!\n");
    else
        client_core(client);
    destroy_client(client);
    return (0);
}