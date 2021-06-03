/*
** EPITECH PROJECT, 2021
** Delivery
** File description:
** load
*/

#include <stdio.h>
#include "clients.h"
#include "server.h"
#include "libs/myteams/logging_server.h"

void load_clients(void)
{
    struct dirent *de;
    char *new_path;
    DIR *dr = opendir("server/save/clients/");
    char *tmp;
    jsnp_t *jsnp;

    while (dr && (de = readdir(dr)) != NULL) {
        if (!strcmp(de->d_name, "..") || \
!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".exist"))
            continue;
        new_path = malloc(sizeof(char) * 100);
        strcpy(new_path, "server/save/clients/");
        strcat(new_path, de->d_name);
        tmp = de->d_name;
        tmp = modif_uuid(tmp);
        strcat(new_path, tmp);
        jsnp = jsnp_parse_file(new_path);
        server_event_user_loaded(get_token(jsnp->value, "Uuid")\
->value->str, get_token(jsnp->value, "Name")->value->str);
    }
    closedir(dr);
}