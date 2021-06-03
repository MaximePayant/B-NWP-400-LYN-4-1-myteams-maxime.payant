/*
** EPITECH PROJECT, 2021
** Delivery
** File description:
** users
*/

#include <stdio.h>
#include "clients.h"
#include "server.h"

void users(server_t *server, client_t *client, const char *command)
{
/*    client_t *current = server->client;

    (void) command;
    dprintf(client->socket, "104 ");
    while (current) {
        dprintf(client->socket, "{%s}", current->uuid_str);
        dprintf(client->socket, "{%s}", current->user_name);
        dprintf(client->socket, "{%d}\n", current->connected);
        current = current->next;
    }
    dprintf(client->socket, "\r\n");
*/


    struct dirent *de;
    char *new_path;
    DIR *dr = opendir("server/save/clients/");
    char *tmp;
    jsnp_t *jsnp;

    dprintf(client->socket, "104 ");
    while (dr && (de = readdir(dr)) != NULL) {
        if (!strcmp(de->d_name, "..") || !strcmp(de->d_name, ".") \
|| !strcmp(de->d_name, ".exist"))
            continue;
        new_path = malloc(sizeof(char) * 100);
        create_path(new_path, de->d_name, tmp);
        jsnp = jsnp_parse_file(new_path);
        dprintf(client->socket, "{%s}", get_token(jsnp->value, "Uuid")->value->str);
        dprintf(client->socket, "{%s}", get_token(jsnp->value, "Name")->value->str);
        dprintf(client->socket, "{%d}\n", get_token(jsnp->value, "Online")->value->primitive);
    }
    dprintf(client->socket, "\r\n");
    closedir(dr);
    return NULL;
}