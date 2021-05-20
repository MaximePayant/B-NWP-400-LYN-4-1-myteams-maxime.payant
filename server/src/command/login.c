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
    strcat(new_uuid, ".txt\0");
    return new_uuid;
}



int check_first_word(const char *str, char *check)
{
    if (strlen(str) < strlen(check))
        return 0;
    for (int i = 0; i != strlen(check); i ++) {
        if (str[i] != check[i])
            return 0;
    }
    return 1;
}

char *find_log(const char *command)
{
    char *log;
    if (!check_first_word(command, "/login"))
        return NULL;
    printf("juif = %d\n", strlen(command));
    if (strlen(command) <= 8)
        return NULL;
    log = malloc(sizeof(char) * strlen(command)-7);
    for (int i = 7, j = 0; i != strlen(command); i ++, j++) {
        log[j] = command[i];
    }
    log[strlen(command)-8] = '\0';
    return(log);
}

void create_txt_log(char *path_folder, char *uuid_str, char *log)
{
    FILE *fPtr;
    char *new_path = malloc(sizeof(char) * 93);
    strcpy(new_path, path_folder);
    uuid_str = modif_uuid(uuid_str);
    strcat(new_path, uuid_str);
    printf("|%s|\n", new_path);
    fPtr = fopen(new_path, "a");
    if(fPtr == NULL)
        printf("Unable to create file.\n");
    fputs("#LOG\n\0", fPtr);
    fputs(log, fPtr);
    fclose(fPtr);
}

char *search_in_file(char *log, char *str)
{
    int test = 0;
    int save = 0;
    int size = 0;
    char *new_log;
    for (int i = 0, j = 0; log[i] != '\0'; i ++) {
        if (log[i] != str[j]) {
            test = 0;
            j = 0;
        }
        while(log[i] == str[j]) {
            test++;
            j++;
        }

        printf("bite = %d et %d\n", test, strlen(str));
        if (test == strlen(str)) {
            save = i;
        }

    }
    for (int i = save+2; log[i] != '\0'; i ++) {
        printf("test = %c\n", log[i]);
        size ++;
    }
    new_log = malloc(sizeof(char) * size);
    test = 0;
    for (int i = save+2; log[i] != '\n'; i ++, test++) {
        new_log[test] = log[i];
    }
    new_log[test] = '\0';
    printf("\nbite = %s\n", new_log);
}

char *check_log_exist(char *log)
{
    struct dirent *de;
    DIR *dr = opendir("save/clients");
    FILE *fp;
    char *path;
    char *tmp;
    char *log_find;
    int i;
    while ((de = readdir(dr)) != NULL) {
        if (!strcmp(de->d_name, "..") || !strcmp(de->d_name, "."))
            continue;
        path = malloc(sizeof(char) * 93);
        strcpy(path, "save/clients/");
        tmp = de->d_name;
        strcat(path, tmp);
        tmp = modif_uuid(tmp);
        strcat(path, tmp);
        printf("%s\n", path);
        fp = fopen(path, "r");
        log_find = malloc(sizeof(char) * ftell(fp));
        i = 0;
        while((path = fgetc(fp)) != EOF) {
            log_find[i] = path;
            i++;
        }
        log_find[i] = '\0';
//        log_find = search_in_file(log_find, "#LOG");
        fclose(fp);
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
    if (/*!check_log_exist*/log) {
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
//        create_txt_log(path_folder, uuid_str, log);
        client->connected = 1;
        client->user_name = log;
        dprintf(client->socket, "Create clients with UUID = %s\r\n", uuid_str);
    }
    else {        
        client->connected = 1;
        client->user_name = log;
      //  uuid_str = get_uid(check_log_exist(log));
        uuid_parse(client->uuid, uuid_str);
        dprintf(client->socket, "Log in account with UUID = %s\r\n", uuid_str);
    }
}
