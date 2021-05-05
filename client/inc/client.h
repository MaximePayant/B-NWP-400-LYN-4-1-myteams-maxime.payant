/*
** EPITECH PROJECT, 2021
** client.h
** File description:
** client.h
*/

#ifndef CLIENT
#define CLIENT

#include <netinet/in.h>

typedef struct client_s
{
    char *ip;
    char *port;
    struct sockaddr_in sock;
    int socket;
} client_t;
#endif //CLIENT
