/*
** EPITECH PROJECT, 2018
** Project
** File description:
** main.c
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lemipc.h"

int	print_help(void)
{
	printf("USAGE\n");
	printf("\t./lemipc PATH TEAM_NUMBER\n");
	printf("\nDESCRIPTION\n");
	printf("\tPATH\t\tpath you'll give to ftok\n");
	printf("\tTEAM_NUMBER\tteam number of ");
	printf("the current champion (greater than 0)\n");
	printf("\t-wall\tActivate wall");
	return (0);
}

int	main(int ac, char **av)
{
	ipcs_t *ipcs;

	srand(time(NULL));
	if ((ac == 2 && ((strcmp(av[1], "--help")) == 0)) || (ac > 4)){
		print_help();
		return (84);
	}
	ipcs = init(av[0]);
	if (ipcs == NULL)
		return (-1);
	ipcs->shm_id = shmget(ipcs->key, (sizeof(node_t) *
		WIDTH * HEIGHT), SHM_R | SHM_W);
	if (ipcs->shm_id == -1)
		init_server(ipcs, av);
	else
		init_client(ipcs, atoi(av[2]));
	return (0);
}
