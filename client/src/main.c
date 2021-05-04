/*
** EPITECH PROJECT, 2021
** man.c
** File description:
** man.c
*/

#include <string.h>
#include <stdio.h>

int help_output(void)
{
    printf("USAGE: ./myteams_cli ip port\n\t");
    printf("ip\tis the server ip address on which"
    " the server socket listens\n");
    printf("\tport\tis the port number on which"
    " the server socket listens.\n");
    return (0);
}

int main(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return (help_output());
}