/*
** EPITECH PROJECT, 2021
** my_teams.h
** File description:
** my_teams.h
*/

#ifndef SERVER
#define SERVER

#include <netinet/in.h>
#include <uuid/uuid.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <malloc.h>
#include "../../libs/myteams/logging_client.h"
#include <dirent.h>

typedef struct client_s
{
    char *user_name;
    int socket;
    int connected;
    struct sockaddr_in data;
    uuid_t uuid;
    struct client_s *next;
}client_t;

typedef struct server_s
{
    struct sockaddr_in sock;
    socklen_t sock_size;
    int port;
    int server_socket;
    fd_set set_save;
    client_t *client;
}server_t;

//init
int init_server(server_t *server);

//Core
void server_core(server_t *server);
void command_handler(server_t *server, client_t *client);

//Client
client_t *create_new_client(server_t *server);
client_t *get_client_by_sclient(server_t *ftp, int socket);
void delete_client(server_t *ftp, int socket);

//Command
void help(server_t *server, client_t *client, const char *command);
void login(server_t *server, client_t *client, const char *command);
void logout(server_t *server, client_t *client, const char *command);

#endif //SERVER
