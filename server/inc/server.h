/*
** EPITECH PROJECT, 2021
** my_teams.h
** File description:
** my_teams.h
*/

#ifndef SERVER
#define SERVER

typedef struct server_s server_t;
typedef struct client_s client_t;

#include <netinet/in.h>
#include <uuid/uuid.h>
#include <bits/types/FILE.h>
#include "libs/json_parser/json_parser.h"
#include "teams.h"

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

struct client_s
{
    char *user_name;
    int socket;
    int connected;
    struct sockaddr_in data;
    uuid_t uuid;
    uuid_t team_uuid;
    uuid_t channel_uuid;
    uuid_t thread_uuid;
    FILE *file;
    struct client_s *next;
};

struct server_s
{
    struct sockaddr_in sock;
    socklen_t sock_size;
    int port;
    int server_socket;
    client_t *client;
    team_t *teams;
};

//Utils
char *get_args(const char *command);
char **get_params(const char *args);

//init
int init_server(server_t *server);

//Core
void server_core(server_t *server);
void command_handler(server_t *server, client_t *client);
void print_new_reply(message_t *message, client_t *client);

//Client
client_t *create_new_client(server_t *server);
client_t *get_client_by_sclient(server_t *ftp, int socket);
client_t *get_client_by_uuid(server_t *server, uuid_t target_uuid);
void delete_client(server_t *ftp, int socket);

//Command
void help(server_t *server, client_t *client, const char *command);
void login(server_t *server, client_t *client, const char *command);
void logout(server_t *server, client_t *client, const char *command);
void create(server_t *server, client_t *client, const char *command);
void list(server_t *server, client_t *client, const char *command);
void info(server_t *server, client_t *client, const char *command);
void use(server_t *server, client_t *client, const char *command);
void subscribe(server_t *server, client_t *client, const char *command);
void unsubscribe(server_t *server, client_t *client, const char *command);
void subscribed(server_t *server, client_t *client, const char *command);

//Save
void save(server_t *server);
server_t *load(int port);
void load_team(server_t *server, jsnp_value_t *token);
void load_channel(team_t *team, jsnp_value_t *token);
void load_thread(channel_t *chan, jsnp_value_t *token);

//time_t converter
char *time_to_string(time_t time);
time_t string_to_time(char *string);

#endif //SERVER