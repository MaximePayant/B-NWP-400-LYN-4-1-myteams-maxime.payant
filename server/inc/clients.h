/*
** EPITECH PROJECT, 2021
** Delivery
** File description:
** clients
*/

#ifndef CLIENTS_H_
#define CLIENTS_H_
#include "server.h"

char *check_exist(char *log, char *search);
char *modif_uuid(char *uuid_str);
int verif_file_exist(char *path);
char *my_itoa(int num, char *str);
char *create_path(char *new_path, char *name, char *tmp);
void create_json_count(char *log, char *path_folder, char *uuid_str);
void call_event_create_count(client_t *client);

#endif /* !CLIENTS_H_ */
