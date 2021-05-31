/*
** EPITECH PROJECT, 2021
** client.h
** File description:
** client.h
*/

#ifndef CLIENT
#define CLIENT

#include <netinet/in.h>
#include <bits/types/FILE.h>

typedef struct client_s
{
    char *ip;
    char *port;
    struct sockaddr_in sock;
    int socket;
    int exit;
    FILE *file;
} client_t;

//Core
void client_core(client_t *client);
void update_set(client_t *client, fd_set *set);

//Command
int command_handler(client_t *client, char *command);
void send_command(client_t *client, char *command);
void code_handler(char *code, char *args);
char **get_return_args(const char *args);
void event_handler(const char *args);

//Code
void code_101(const char *args);
void code_102(const char *args);
void code_106(const char *args);
void code_107(const char *args);
void code_108(const char *args);
void code_109(const char *args);
void code_110(const char *args);
void code_111(const char *args);
void code_112(const char *args);
void code_113(const char *args);
void code_114(const char *args);

void code_439(const char *args);
void code_440(const char *args);
void code_441(const char *args);
void code_442(const char *args);
void code_443(const char *args);
void code_444(const char *args);

#endif //CLIENT
