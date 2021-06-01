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

void load_clients()
{
    
    struct dirent *de;
    char *new_path;
    DIR *dr = opendir("server/save/clients/");
    char *tmp;
    jsnp_t *jsnp;
    char *jew;

    printf("JUIFJUIFJUIF\n");

/*
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
        jew = jsnp_read_file(new_path);
        

        printf("juif = %s\n", de->d_name);
    
    }
    */
    closedir(dr);
}