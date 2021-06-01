/*
** EPITECH PROJECT, 2021
** logout.c
** File description:
** logout.c
*/

#include <stdio.h>
#include "clients.h"
#include <malloc.h>
#include "server.h"
#include "libs/myteams/logging_server.h"

void logout(server_t *server, client_t *client, const char *command)
{
    jsnp_t *jsnp = jsnp_parse_file(check_exist(client->user_name, "Name"));
    char *path_folder = malloc(sizeof(char) * 58);
    char *uuid_str = strdup(client->uuid_str);
    (void) command;

    if (client->connected) {
        client->connected = 0;
        server_event_user_logged_out(client->uuid_str);
        dprintf(client->socket, "102 Disconnection successfully{%s}{%s}\r\n",
        client->uuid_str, client->user_name);


        strcpy(path_folder, "server/save/clients/");
        strcat(path_folder, client->uuid_str);

        jsnp = create_jsnp();
        object_emplace_string_back(jsnp->value, "Name", client->user_name);
        object_emplace_string_back(jsnp->value, "Uuid", client->uuid_str);
        object_emplace_primitive_back(jsnp->value, "Online", 0);
        char *new_path = malloc(sizeof(char) * 100);
        strcpy(new_path, path_folder);
        uuid_str = modif_uuid(uuid_str);
        strcat(new_path, uuid_str);
        write_jsnp(jsnp, new_path);

        delete_client(server, client->uuid);
        return;
    }
    dprintf(client->socket, "440 Disconnection successfully\r\n");
}