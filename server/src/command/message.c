/*
** EPITECH PROJECT, 2021
** Delivery
** File description:
** message
*/


#include <stdio.h>
#include "server.h"
#include "clients.h"

void message(server_t *server, client_t *client, const char *command)
{
    (void)server;
    char *new_command = strdup(command);
    char *target = NULL;
    char *path_target = malloc(sizeof(char) * 110);
    char *m = malloc(sizeof(char) * 30);


    strtok(new_command, " ");
    target = strtok(NULL, "\"");
    
    strcpy(path_target, "server/save/clients/");
    strcat(path_target, client->uuid_str);
    strcat(path_target, "/msg:");
    strcat(path_target, target);
    strcat(path_target, ".json\0");
    jsnp_t *jnsp = create_jsnp();

    printf("\nfile = %s\n", path_target);
    jnsp = jsnp_parse_file(path_target);
    
    dprintf(client->socket, "107 ");
    dprintf(client->socket, " {%s} ", get_token(jnsp->value, "Nbr_msg")->value->str);
    for(int i = 0; i != atoi(get_token(jnsp->value, "Nbr_msg")->value->str); i++) {
        dprintf(client->socket, " {%s} ", get_token(get_value(get_token(jnsp->value, my_itoa(i+1, m))->value, 1), "Message")->value->str);
        dprintf(client->socket, " {%s} ", get_token(get_value(get_token(jnsp->value, my_itoa(i+1, m))->value, 1), "Heure")->value->str);
        dprintf(client->socket, " {%s} ", get_token(get_value(get_token(jnsp->value, my_itoa(i+1, m))->value, 1), "Uuid target")->value->str);
//        dprintf(client->socket, " {%s} ", get_token(get_value(get_token(jnsp->value, my_itoa(i+1, m))->value, 1), "Uuid home")->value->str);
    }
    dprintf(client->socket, "\r\n");
}