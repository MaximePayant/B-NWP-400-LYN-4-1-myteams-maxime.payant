/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** load.c
*/

#include <stdlib.h>

#include "libs/json_parser/json_parser.h"
#include "server.h"

static server_t *init_struct(int port)
{
    server_t *new_server = malloc(sizeof(server_t));

    new_server->sock = (struct sockaddr_in){ 0 };
    new_server->sock_size = sizeof(new_server->sock);
    new_server->port = port;
    new_server->client = NULL;
    new_server->server_socket = -1;
    new_server->teams = NULL;
    return (new_server);
}

server_t *load(int port)
{
    jsnp_t *jsnp = jsnp_parse_file("server/save/server.json");
    server_t *server = init_struct(port);

    if (!jsnp)
        return (server);
    disp_jsnp(jsnp);
    for (jsnp_value_t *it = get_token(jsnp->value, "Teams")->value->array.lh_first; it; it = it->next.le_next)
        load_team(server, it);
    free(jsnp);


    for (team_t *team = server->teams; team; team = team->next) {
        printf("Team name: <%s>\n", team->name);
        for (channel_t *chan = team->channels; chan; chan = chan->next) {
            printf("Channel name: <%s>\n", chan->name);
            for (thread_t *thrd = chan->threads; thrd; thrd = thrd->next) {
                printf("Threan name: <%s>\n", thrd->name);
                for (message_t *mess = thrd->message; mess; mess = mess->next)
                    printf("Message: <%s>\n", mess->core);
            }
        }
    }

    return (server);
}