/*
** EPITECH PROJECT, 2021
** Delivery
** File description:
** login_util
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

char *create_path(char *new_path, char *name)
{
    char *tmp;
    strcpy(new_path, "server/save/clients/");
    strcat(new_path, name);
    tmp = name;
    tmp = modif_uuid(tmp);
    strcat(new_path, tmp);
    return (new_path);
}

char *check_exist(char *log, char *search)
{
    struct dirent *de;
    char *new_path;
    DIR *dr = opendir("server/save/clients/");
    jsnp_t *jsnp;

    while (dr && (de = readdir(dr)) != NULL) {
        if (!strcmp(de->d_name, "..") || !strcmp(de->d_name, ".") \
|| !strcmp(de->d_name, ".exist"))
            continue;
        new_path = malloc(sizeof(char) * 100);
        create_path(new_path, de->d_name);
        jsnp = jsnp_parse_file(new_path);
        if (!strcmp(log, get_token(jsnp->value, search)->value->str)) {
            closedir(dr);
            return (new_path);
        }
    }
    closedir(dr);
    return NULL;
}

void call_event_create_count(client_t *client)
{
    server_event_user_created(client->uuid_str, client->user_name);
    server_event_user_logged_in(client->uuid_str);
    dprintf(client->socket, "101 create log successfully{%s}{%s}\r\n",
    client->uuid_str, client->user_name);
}

void create_json_count(char *log, char *path_folder, char *uuid_str)
{
    jsnp_t *jsnp = create_jsnp();
    char *new_path = malloc(sizeof(char) * 100);

    object_emplace_string_back(jsnp->value, "Name", log);
    object_emplace_string_back(jsnp->value, "Uuid", uuid_str);
    object_emplace_primitive_back(jsnp->value, "Online", 1);
    strcpy(new_path, path_folder);
    uuid_str = modif_uuid(uuid_str);
    strcat(new_path, uuid_str);
    write_jsnp(jsnp, new_path);
    free_jsnp(jsnp);

}