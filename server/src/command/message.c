/*
** EPITECH PROJECT, 2021
** Delivery
** File description:
** message
*/


#include <stdio.h>
#include "server.h"

void message(server_t *server, client_t *client, const char *command)
{
    (void)server;
    char *new_command = strdup(command);
    char *target = NULL;
    char *path_target = malloc(sizeof(char) * 110);
    char *json_str;



    strtok(new_command, " ");
    target = strtok(NULL, " ");
    
    strcpy(path_target, "server/save/clients/");
    strcat(path_target, client->uuid_str);
    strcat(path_target, "/msg:");
    strcat(path_target, target);
    strcat(path_target, ".json\0");
    jsnp_t *jnsp = create_jsnp();
    jnsp = jsnp_parse_file(path_target);
    disp_jsnp(jnsp);
    json_str = jsnp_read_file(path_target);

    dprintf(client->socket, "107 {%s},{%s},{%s}\r\n", target, "heure", json_str);
}