/*
** EPITECH PROJECT, 2018
** Project
** File description:
** init.c
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <stdlib.h>
#include "lemipc.h"

void create_walls(node_t *map)
{
	int i = 0;

	for (int walls = 0; walls < (WIDTH * HEIGHT) / 20; walls++){
		i = (rand() % (WIDTH * HEIGHT - 1));
		while (map[i].team != 0 && map[i].team != WALL)
			i = (rand() % (WIDTH * HEIGHT - 1));
		map[i].team = WALL;
		}
}

void	*init_map(ipcs_t *ipcs, node_t *map, char **av)
{
	int i = 0;

	if ((ipcs->sem_id = semget(ipcs->key, 1, IPC_CREAT
	| SHM_R | SHM_W)) == -1)
		return ((void *)-1);
	semctl(ipcs->sem_id, 0, SETVAL, 1);
	for (size_t x = 0; x < WIDTH; x++)
	{
		for (size_t y = 0; y < HEIGHT; y++)
		{
			map[i].team = 0;
			i++;
		}
	}
	if (av[3] && strcmp(av[3], "-wall") == 0)
		create_walls(map);
	return (NULL);
}

size_t init_player(node_t *map, ipcs_t *ipcs, int team)
{
	size_t	pos;

	lock_sem(ipcs->sem_id);
	pos = (size_t)(rand() % (WIDTH * HEIGHT - 1));
	while (map[pos].team != 0)
		pos = (size_t)(rand() % (WIDTH * HEIGHT - 1));
	map[pos].team = team;
	unlock_sem(ipcs->sem_id);
	return (pos);
}


int init_server(ipcs_t *ipcs, char **av)
{
	size_t position;

	ipcs->shm_id = shmget(ipcs->key, (sizeof(node_t) *
	WIDTH * HEIGHT), IPC_CREAT | SHM_R | SHM_W);
	if (ipcs->shm_id == -1)
		return (-1);
	void *addr = shmat(ipcs->shm_id, NULL, SHM_R | SHM_W);
	if (addr == (void *)-1)
		return (-1);
	ipcs->msg_id = msgget(ipcs->key, SHM_R | SHM_W);
	if (ipcs->msg_id == -1)
		ipcs->msg_id = msgget(ipcs->key, IPC_CREAT | SHM_R | SHM_W);
	if (init_map(ipcs, addr, av) == (void *)-1)
		return (-1);
	position = init_player(addr, ipcs, atoi(av[2]));
	if (fork() == 0)
		display_map((node_t *)addr, ipcs);
	else
		fight(addr, ipcs, position);
	return (0);
}

int init_client(ipcs_t *ipcs, int team)
{
	void *addr;
	int position;

	ipcs->sem_id = semget(ipcs->key, 1, SHM_R | SHM_W);
	ipcs->msg_id = msgget(ipcs->key, SHM_R | SHM_W);
	addr = shmat(ipcs->shm_id, NULL, SHM_R | SHM_W);
	if (addr == (void *)-1)
		return (-1);
	position = init_player(addr, ipcs, team);
	fight(addr, ipcs, position);
	return (0);
}
