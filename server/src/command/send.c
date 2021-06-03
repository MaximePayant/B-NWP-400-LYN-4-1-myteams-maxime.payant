/*
** EPITECH PROJECT, 2021
** Delivery
** File description:
** send
*/

#include <stdio.h>
#include "server.h"
#include "clients.h"
#include "json_list.h"
#include <stdlib.h>
#include <string.h>
#include "libs/myteams/logging_server.h"

char *my_itoa(int num, char *str)
{
    if(str == NULL)
        return NULL;
    sprintf(str, "%d", num);
    return str;
}

int verif_file_exist(char *path)
{
    FILE *file;

    file = fopen(path, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    else
        return 0; 
}

void send_message(server_t *server, client_t *client, const char *command)
{
    (void)server;
    char *new_command = strdup(command);
    char *target = NULL;
    char *message = NULL;
    jsnp_t *jnsp;
    jsnp_token_t *msg;
//    jsnp_value_t *value_nbr;
    jsnp_token_t *nbr;
    time_t now;
    int j = 0;
    struct tm * timeinfo;
    char *path_target = malloc(sizeof(char) * 110);
    char *path_home = malloc(sizeof(char) * 110);

    strtok(new_command, " ");
    target = strtok(NULL, " \"");
    strtok(NULL, "\"");

    message = strtok(NULL, "\"");
    
    if (!message || !target) {
        dprintf(client->socket, "440 Invalide message or target\r\n");
        return;
    }
    printf("target = %s, message %s\n", target, message);
    if (check_exist(target, "Uuid")) {
        printf("uuid %s exist\n", target);
        time(&now);
        strcpy(path_home, "server/save/clients/");
        strcpy(path_target, "server/save/clients/");
        strcat(path_home, client->uuid_str);
        strcat(path_target, target);
        strcat(path_home, "/msg:");
        strcat(path_target, "/msg:");
        strcat(path_home, target);
        strcat(path_target, client->uuid_str);
        strcat(path_home, ".json\0");
        strcat(path_target, ".json\0");
        jnsp = create_jsnp();
        if (verif_file_exist(path_target))
            jnsp = jsnp_parse_file(path_target);
        else
            nbr = object_emplace_string_back(jnsp->value, "Nbr_msg", "0");
        nbr = get_token(jnsp->value, "Nbr_msg");
        j = atoi(nbr->value->str);
        j++;
        msg = object_emplace_array_back(jnsp->value, my_itoa(j, nbr->value->str));
        jsnp_value_t *value = array_emplace_object_back(msg->value);
        object_emplace_string_back(value, "Uuid target", target);
        object_emplace_string_back(value, "Uuid home", client->uuid_str);
        object_emplace_string_back(value, "Heure", time_to_string(now));
        object_emplace_string_back(value, "Message", message);

        write_jsnp(jnsp, path_target);
        write_jsnp(jnsp, path_home);
        server_event_private_message_sent(client->uuid_str, target, message);

        dprintf(client->socket, "106 to uuid {%s} message {%s}\r\n", target, message);
        
    }
    else
        dprintf(client->socket, "440 Invalide message or target\r\n");

}