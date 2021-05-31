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

char *modif_uuid(char *uuid_str)
{
    char *new_uuid = malloc(sizeof(char) * 43);
    strcpy(new_uuid, "/");
    strcat(new_uuid, uuid_str);
    strcat(new_uuid, ".json\0");
    return new_uuid;
}

char *check_exist(char *log, char *search)
{
    struct dirent *de;
    char *new_path;
    DIR *dr = opendir("server/save/clients");
    char *tmp;
    jsnp_t *jsnp;

    while (dr && (de = readdir(dr)) != NULL) {
        if (!strcmp(de->d_name, "..") || !strcmp(de->d_name, ".") || !strcmp(de->d_name, ".exist"))
            continue;
        new_path = malloc(sizeof(char) * 100);
        strcpy(new_path, "server/save/clients/");
        strcat(new_path, de->d_name);
        tmp = de->d_name;
        tmp = modif_uuid(tmp);
        strcat(new_path, tmp);
        jsnp = jsnp_parse_file(new_path);
        if (!strcmp(log, get_token(jsnp->value, search)->value->str)) {
            closedir(dr);
            return (new_path);
        }
    }
    closedir(dr);    
    return NULL;
}

void login(server_t *server, client_t *client, const char *command)
{
    struct stat st = {0};
    jsnp_t *jsnp;
    char *new_command = strdup(command);
    char *log = NULL;
    char *path_folder = NULL; 
    char *uuid_str;
    (void) server;

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
        path_folder = malloc(sizeof(char) * 58);
        uuid_str = malloc(sizeof(char) * 37);
        strcpy(path_folder, "server/save/clients/");
        uuid_generate(client->uuid);
        uuid_unparse_lower(client->uuid, uuid_str);
        strcat(path_folder, uuid_str);
        if (stat(path_folder, &st) == -1)
            mkdir(path_folder, 0755);
        jsnp = create_jsnp();
        object_emplace_string_back(jsnp->value, "Name", log);
        object_emplace_string_back(jsnp->value, "Uuid", uuid_str);
        object_emplace_primitive_back(jsnp->value, "Online", 1);
        char *new_path = malloc(sizeof(char) * 100);
        strcpy(new_path, path_folder);
        uuid_str = modif_uuid(uuid_str);
        strcat(new_path, uuid_str);
        write_jsnp(jsnp, new_path); 
        client->connected = 1;
        client->user_name = strdup(log);
        uuid_unparse_lower(client->uuid, uuid_str);
        client->uuid_str = strdup(uuid_str);
        server_event_user_created(client->uuid_str, client->user_name);
        server_event_user_logged_in(client->uuid_str);
        dprintf(client->socket, "101 create log successfully{%s}{%s}\r\n",
        client->uuid_str, client->user_name);
        free_jsnp(jsnp);
        free(path_folder);
        free(uuid_str);
    }
    else {
        path_folder = malloc(sizeof(char) * 58);
        uuid_str = malloc(sizeof(char) * 37);
        jsnp = jsnp_parse_file(check_exist(log, "Name"));
        client->connected = 1;
        client->user_name = strdup(get_token(jsnp->value, "Name")->value->str);
        uuid_str = get_token(jsnp->value, "Uuid")->value->str;
        client->uuid_str = strdup(uuid_str);
        uuid_parse(uuid_str, client->uuid);
        server_event_user_loaded(client->uuid_str, client->user_name);
        server_event_user_logged_in(client->uuid_str);


        strcpy(path_folder, "server/save/clients/");
        strcat(path_folder, uuid_str);

        jsnp = create_jsnp();
        object_emplace_string_back(jsnp->value, "Name", log);
        object_emplace_string_back(jsnp->value, "Uuid", uuid_str);
        object_emplace_primitive_back(jsnp->value, "Online", 1);
        char *new_path = malloc(sizeof(char) * 100);
        strcpy(new_path, path_folder);
        uuid_str = modif_uuid(uuid_str);
        strcat(new_path, uuid_str);
        write_jsnp(jsnp, new_path);

        dprintf(client->socket, "101 log successfully{%s}{%s}\r\n",
        client->uuid_str, client->user_name);
        free_jsnp(jsnp);
    }
}
