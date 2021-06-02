/*
** EPITECH PROJECT, 2021
** event_handler.c
** File description:
** event_handler.c
*/

#include <string.h>
#include "client.h"
#include "libs/myteams/logging_client.h"

void event_handler(const char *args)
{
    char **list_args = get_return_args(args);

    if (strcmp(list_args[0], "team") == 0)
        client_event_team_created(list_args[1], list_args[2], list_args[3]);
    if (strcmp(list_args[0], "channel") == 0)
        client_event_channel_created(list_args[1], list_args[2], list_args[3]);
    if (strcmp(list_args[0], "thread") == 0)
        client_event_thread_created(list_args[1], list_args[2], time(NULL), list_args[4], list_args[5]);
    if (strcmp(list_args[0], "reply") == 0)
        client_event_thread_reply_received(list_args[1], list_args[2], list_args[3], list_args[4]);
    if (strcmp(list_args[0], "login") == 0)
        client_event_logged_in(list_args[1], list_args[2]);
    if (strcmp(list_args[0], "logout") == 0)
        client_event_logged_out(list_args[1], list_args[2]);
}