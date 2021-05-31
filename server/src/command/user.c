/*
** EPITECH PROJECT, 2021
** Delivery
** File description:
** user
*/

#include <stdio.h>
#include "clients.h"
#include "server.h"

void user(server_t *server, client_t *client, const char *command)
{
    char *new_command = strdup(command);
    char *target = NULL;
    char *path = malloc(sizeof(char) * 110);
    jsnp_t *jnsp;


    strtok(new_command, " ");
    target = strtok(NULL, " \"");

    if (!target) {
        dprintf(client->socket, "444 Invalide target {%s}\r\n", target);
    }
    if (check_exist(target, "Uuid")) {

        strcpy(path, "server/save/clients/");
        strcat(path, target);
        strcat(path, "/");
        strcat(path, target);
        strcat(path, ".json\0");
        jnsp = create_jsnp();
        if (verif_file_exist(path))
            jnsp = jsnp_parse_file(path);
        else
            dprintf(client->socket, "444 Invalide target {%s}\r\n", target);
       // disp_jsnp(jnsp);
        dprintf(client->socket, "105 {%s}{%s}{%d}\r\n", target,  get_token(jnsp->value, "Name")->value->str, get_token(jnsp->value, "Online")->value->primitive);
    }
}