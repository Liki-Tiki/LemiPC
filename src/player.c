/*
** EPITECH PROJECT, 2018
** Project
** File description:
** player.c
*/

#include <unistd.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lemipc.h"

int *get_xy(int pos)
{
	int *ret;

	ret = malloc((3 * sizeof(int)));
	if (!ret)
		return (NULL);
	ret[1] = 0;
	ret[2] = 0;
	for (int tmp = pos; tmp > WIDTH - 1; ret[1]++) {
		tmp -= WIDTH;
	}
	ret[0] = pos;
	while (ret[0] > WIDTH - 1)
		ret[0] -= WIDTH;
	return (ret);
}

int distance(int a, int b)
{
	int *_a;
	int *_b;
	int dist;

	_a = get_xy(a);
	_b = get_xy(b);
	dist = sqrt(pow(_b[0] - _a[0], 2) + pow(_b[1] - _b[0], 2));
	return (dist);
}

int go_to(int current_pos_mem, int pos)
{
	int *current_pos;
	int *togo_pos;
	int new_pos_mem = current_pos_mem;

	current_pos = get_xy(current_pos_mem);
	togo_pos = get_xy(pos);
	if (current_pos[1] > togo_pos[1] && current_pos[1] > 0)
		new_pos_mem -= WIDTH;
	if (current_pos[1] < togo_pos[1] && togo_pos[1] < HEIGHT - 1)
		new_pos_mem += WIDTH;
	if (current_pos[0] > togo_pos[0] && current_pos[0] > 0)
		new_pos_mem -= 1;
	if (current_pos[0] < togo_pos[0] && current_pos[1] < WIDTH - 1)
		new_pos_mem += 1;
	return (new_pos_mem);
}

int find_a_victim(node_t *map, int pos, ipcs_t *ipcs)
{
	msg_t msg;
	int dist = WIDTH * HEIGHT;
	int save;

	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		if (map[i].team != 0 && map[i].team != WALL &&
			map[i].team != map[pos].team
		&& distance(pos, i) < dist)
		{
			dist = distance(pos, i);
			msg.type = map[pos].team;
			save = i;
		}
	}
	msg.position = save;
	msgsnd(ipcs->msg_id, &msg, sizeof(msg_t), msg.type | IPC_NOWAIT);
	return (go_to(pos, save));
}

int fight(node_t *map, ipcs_t *ipcs, int pos)
{
	int alive = 1;
	while (is_there_more_than_one_team(map) == 0){
		usleep(100000);
	}
	printf("Joined team : ");
	print_soldier(map[pos].team);
	printf("\n");
	while (alive == 1 && is_there_more_than_one_team(map) != 0){
		lock_sem(ipcs->sem_id);
		alive = is_alive(map, pos);
		pos = move(map, pos, ipcs);
		unlock_sem(ipcs->sem_id);
		usleep(100000);
	}
	return (0);
}
