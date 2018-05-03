/*
** EPITECH PROJECT, 2018
** k
** File description:
** k
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include "lemipc.h"

void sort_asc(int *tab, infos_t *infos)
{
	int tmp;
	int done = 0;

	while (done == 0){
		done = 1;
		for (int i = 0; tab[i]; i++){
			if (tab[i + 1] && tab[i] > tab[i + 1]){
				tmp = tab[i + 1];
				tab[i + 1] = tab[i];
				tab[i] = tmp;
				done = 0;
			}
		}
	}
	infos->amount = infos->stock;
	infos->teams = infos->teams2;

}

void fill_infos(infos_t *infos, node_t *map)
{
	int idx = 0;
	infos->stock = 0;

	infos->teams2 = malloc(WIDTH * HEIGHT * sizeof(int));
	for (int i = 0; i < HEIGHT * WIDTH; i++){
		if (map[i].team != 0 && map[i].team != WALL){
			infos->fail = 0;
			for (int j = 0; infos->teams2[j]; j++){
				if (infos->teams2[j] == map[i].team){
					infos->fail = 1;
					continue;
				}
			}
			if (infos->fail == 0){
				infos->teams2[idx++] = map[i].team;
				infos->stock++;
			}
		}
	}
	sort_asc(infos->teams2, infos);
}

void print_infos(infos_t *infos, node_t *map)
{
	printf ("-------\nTeams alive : %d [ ", infos->amount);
	for (int i = 0; infos->teams[i]; i++){
			print_soldier(infos->teams[i]);
			printf("(%d)", get_alive_by_team(map, infos->teams[i]));
			printf(" ");
	}
	printf("]\n-------\n");
}

void print_everything(ipcs_t *ipcs, node_t *map, infos_t *infos)
{
	lock_sem(ipcs->sem_id);
	printf("\e[1;1H\e[2J");
	print_map(map);
	fill_infos(infos, map);
	print_infos(infos, map);
	usleep(100000);
	unlock_sem(ipcs->sem_id);
}

void display_map(node_t *map, ipcs_t *ipcs)
{
	int i = 0;
	infos_t *infos;

	infos = malloc(sizeof(infos_t));
	while (is_there_more_than_one_team(map) == 0)
		usleep(100000);
	while (is_there_more_than_one_team(map) != 0)
		print_everything(ipcs, map, infos);
	while ((i < WIDTH * HEIGHT - 1) && (map[i].team == 0 ||
		map[i].team == WALL)){
		i++;
	}
	printf("Team ");
	print_soldier(map[i].team);
	printf(" won with "COLOR_GREEN_BRIGHT"%d soldiers"COLOR_RESET
			" still alive !\n"
		, get_alive_by_team(map, map[i].team));
	semctl(ipcs->sem_id, 1, IPC_RMID);
	shmctl(ipcs->shm_id, IPC_RMID, NULL);
	msgctl(ipcs->msg_id, IPC_RMID, NULL);
}
