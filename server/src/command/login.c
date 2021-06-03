/*
** EPITECH PROJECT, 2021
** login.c
** File description:
** login.c
*/

#include <stdio.h>
#include "clients.h"
#include "server.h"
#include "libs/myteams/logging_server.h"

static void send_event(server_t *server, client_t *client)
{
    client_t *current = server->client;

    while (current) {
        if (!current->connected) {
            current = current->next;
            continue;
        }
        dprintf(current->socket, "222 New user connected{login}{%s}"
        "{%s}\r\n", client->uuid_str, client->user_name);
        current = current->next;
    }
}

void create_count(server_t *server, client_t *client, char *log)
{
    struct stat st = {0};
    char *path_folder = malloc(sizeof(char) * 58);
    char *uuid_str = malloc(sizeof(char) * 37);

    strcpy(path_folder, "server/save/clients/");
    uuid_generate(client->uuid);
    uuid_unparse_lower(client->uuid, uuid_str);
    strcat(path_folder, uuid_str);
    if (stat(path_folder, &st) == -1)
        mkdir(path_folder, 0755);
    create_json_count(log, path_folder, uuid_str);
    client->connected = 1;
    client->user_name = strdup(log);
    uuid_unparse_lower(client->uuid, uuid_str);
    client->uuid_str = strdup(uuid_str);
    call_event_create_count(client);
    send_event(server, client);
    free(path_folder);
    free(uuid_str);
}

void create_json_log(jsnp_t *jsnp, char *log, char *path_folder, char *uuid_str)
{
    char *new_path = malloc(sizeof(char) * 100);

    jsnp = create_jsnp();
    object_emplace_string_back(jsnp->value, "Name", log);
    object_emplace_string_back(jsnp->value, "Uuid", uuid_str);
    object_emplace_primitive_back(jsnp->value, "Online", 1);
    strcpy(new_path, path_folder);
    uuid_str = modif_uuid(uuid_str);
    strcat(new_path, uuid_str);
    write_jsnp(jsnp, new_path);
    free_jsnp(jsnp);
}

void log_count(server_t *server, client_t *client, char *log)
{
    jsnp_t *jsnp = jsnp_parse_file(check_exist(log, "Name"));
    char *path_folder = malloc(sizeof(char) * 58);
    char *uuid_str = malloc(sizeof(char) * 37);

    client->connected = 1;
    client->user_name = strdup(get_token(jsnp->value, "Name")->value->str);
    uuid_str = get_token(jsnp->value, "Uuid")->value->str;
    client->uuid_str = strdup(uuid_str);
    uuid_parse(uuid_str, client->uuid);
    server_event_user_loaded(client->uuid_str, client->user_name);
    server_event_user_logged_in(client->uuid_str);
    strcpy(path_folder, "server/save/clients/");
    strcat(path_folder, uuid_str);
    create_json_log(jsnp, log, path_folder, uuid_str);
    dprintf(client->socket, "101 log successfully{%s}{%s}\r\n",
    client->uuid_str, client->user_name);
    send_event(server, client);

}

void login(server_t *server, client_t *client, const char *command)
{
    char *new_command = strdup(command);
    char *log = NULL;




    if (client->connected == 1) {
        dprintf(client->socket, "401 Already connect, you need loggout\r\n");
        return;
    }
    strtok(new_command, " ");
    log = strtok(NULL, "\"");
    if (!log) {
        dprintf(client->socket, "401 Enter a valid log please\r\n");
        client->connected = 0;
        return;
    }
    if (!check_exist(log, "Name")) {
        create_count(server, client, log);
    }
    else {

        log_count(server, client, log);


    }
}
