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

//Core
void client_core(client_t *client);

//Command
int command_handler(client_t *client, char *command);
void send_command(client_t *client, char *command);

#endif //CLIENT
