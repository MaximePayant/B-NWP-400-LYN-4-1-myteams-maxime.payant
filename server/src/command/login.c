/*
** EPITECH PROJECT, 2021
** login.c
** File description:
** login.c
*/

#include <stdio.h>
#include "server.h"

char *modif_uuid(char *uuid_str)
{
    char *new_uuid = malloc(sizeof(char) * 43);
    strcpy(new_uuid, "/");
    strcat(new_uuid, uuid_str);
    strcat(new_uuid, ".json\0");
    return new_uuid;
}

char *check_log_exist(char *log)
{

    struct dirent *de;
    char *new_path;

    DIR *dr = opendir("server/save/clients");
    FILE *fp;
    char *path;
    char *tmp;
    char *log_find;
    int i;
    while ((de = readdir(dr)) != NULL) {
        if (!strcmp(de->d_name, "..") || !strcmp(de->d_name, "."))
            continue;
        new_path = malloc(sizeof(char) * 100);
        strcpy(new_path, "server/save/clients/");
        strcat(new_path, de->d_name);
        tmp = de->d_name;
        tmp = modif_uuid(tmp);
        strcat(new_path, tmp);
        printf("\n|%s|\n", new_path);
        jsnp_t *jsnp = jsnp_parse_file(new_path);
        
        jsnp_token_t *test = get_token(jsnp->value, "Name");
        if (!strcmp(log, test->value->str)) {
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
    char *new_command = strdup(command);
    char *log = NULL;
    char *path_folder = NULL; 
    char *uuid_str;

    strtok(new_command, " ");
    log = strtok(NULL, " ");    
    if (!log) {
        dprintf(client->socket, "Enter a valid log please\r\n");
        return;
    }
    if (!check_log_exist(log)) {
        path_folder = malloc(sizeof(char) * 58);
        uuid_str = malloc(sizeof(char) * 37);
        strcpy(path_folder, "server/save/clients/");
        uuid_generate(client->uuid);
        uuid_unparse_lower(client->uuid, uuid_str);
        strcat(path_folder, uuid_str);
        printf("generate uuid=%s\n", path_folder);
        if (stat(path_folder, &st) == -1) {
            mkdir(path_folder, 0755);
            printf("bite\n");
        }


    jsnp_t *jsnp = create_jsnp();

    if (!jsnp) {
        printf("NOP\n");
        return (84);
    }

    object_emplace_string_back(jsnp->value, "Name", log);
    object_emplace_string_back(jsnp->value, "Uuid", uuid_str);

    disp_jsnp(jsnp);
    char *new_path = malloc(sizeof(char) * 100);
    strcpy(new_path, path_folder);
    uuid_str = modif_uuid(uuid_str);
    strcat(new_path, uuid_str);
    write_jsnp(jsnp, new_path);

    free_jsnp(jsnp);
        client->connected = 1;
        client->user_name = log;
        uuid_unparse_lower(client->uuid, uuid_str);
        dprintf(client->socket, "Create clients with UUID = %s\r\n", uuid_str);
    }
    else {        
        jsnp_t *jsnp2 = jsnp_parse_file(check_log_exist(log));

        client->connected = 1;
        client->user_name = get_token(jsnp2->value, "Name")->value->str;
        uuid_str = get_token(jsnp2->value, "Uuid")->value->str;
        uuid_parse(uuid_str, client->uuid);
        printf("caca %s\n", check_log_exist(log));
        dprintf(client->socket, "Log in account with UUID = %s\r\n", uuid_str);
    free_jsnp(jsnp2);

    }

}
