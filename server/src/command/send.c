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

void send_message(server_t *server, client_t *client, const char *command)
{
    char *new_command = strdup(command);
    char *target = NULL;
    char *message = NULL;
    jsnp_t *jnsp;
    jsnp_token_t *msg;
    time_t now;
    struct tm * timeinfo;
    char *path_target = malloc(sizeof(char) * 110);
    char *path_home = malloc(sizeof(char) * 110);



    strtok(new_command, " ");
    target = strtok(NULL, " ");
    message = strtok(NULL, " ");
    if (!message || !target) {
        dprintf(client->socket, "Invalide message or target\r\n");
        return;
    }
    dprintf(client->socket, "Send message %s to uuid %s\r\n", message, target);
    if (check_exist(target, "Uuid")) {
        printf("uuid %s exist\n", target);
        time(&now);
        timeinfo = localtime(&now);
        printf("Current local time and date: %s", asctime (timeinfo));
        jnsp = create_jsnp();
        msg = object_emplace_array_back(jnsp->value, "Msg");
        jsnp_value_t *friend1 = array_emplace_object_back(msg->value);
        object_emplace_string_back(friend1, "Uuid target", target);
        object_emplace_string_back(friend1, "Uuid home", client->uuid_str);
        object_emplace_string_back(friend1, "Heure", asctime(timeinfo));
        object_emplace_string_back(friend1, "Message", message);
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
        write_jsnp(jnsp, path_target);
        write_jsnp(jnsp, path_home);

//        disp_jsnp(jnsp);
    }
}