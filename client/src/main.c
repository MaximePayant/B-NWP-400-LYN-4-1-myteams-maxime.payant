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
#include "client.h"

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

    new_client->port = NULL;
    new_client->ip = NULL;
    new_client->sock = (struct sockaddr_in){ 0 };
    new_client->socket = -1;
    return (new_client);
}

int main(int ac, char **av)
{
    client_t *client = NULL;

    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return (help_output());
    if (ac != 3)
        return (84);
    client = init_struct(av);
    client->ip = av[1];
    client->port = av[2];

    client->socket = socket(AF_INET, SOCK_STREAM, 0);
    client->sock.sin_port = htons(atoi(client->port));
    client->sock.sin_addr.s_addr = inet_addr(client->ip);
    client->sock.sin_family = AF_INET;

    if (connect(client->socket, (struct sockaddr *) &client->sock, sizeof(client->sock)) == -1)
        printf("Connection refused!\n");
    else {
        printf("Connection successful!\n");
    }
    close(client->socket);
}