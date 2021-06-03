/*
** EPITECH PROJECT, 2021
** setup_server.c
** File description:
** setup_server.c
*/

#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include "server.h"

int bind_socket(server_t *server)
{
    int result = 0;

    result = bind(server->server_socket, (struct sockaddr *)&server->sock,
    server->sock_size);
    if (result == -1) {
        printf("[SERVER] Closing socket...\n");
        close(server->server_socket);
        return (1);
    }
    return (0);
}

int listen_socket(server_t *server)
{
    int result = listen(server->server_socket, 5);

    if (result == -1) {
        printf("[SERVER] Closing socket....\n");
        close(server->server_socket);
        return (1);
    }
    return (0);
}

int init_server(server_t *server)
{
    server->server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server->server_socket == -1) {
        return (1);
    }
    printf("[SERVER] Socket %d is now open on TCP/IP mode\n",
    server->server_socket);
    server->sock.sin_family = AF_INET;
    server->sock.sin_port = htons(server->port);
    server->sock.sin_addr.s_addr = htonl(INADDR_ANY);
    load_clients();
    if (bind_socket(server) == 1 || listen_socket(server) == 1)
        return (1);
    return (0);
}