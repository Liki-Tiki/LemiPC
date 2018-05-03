/*
** EPITECH PROJECT, 2018
** player2
** File description:
** player2
*/

#include <unistd.h>
#include <sys/msg.h>
#include <stdlib.h>
#include "lemipc.h"

int find_free_case(node_t *map, int pos)
{
	int *coords = get_xy(pos);
	int direction = rand() % 4;

	if (direction == 0 && coords[1] < (HEIGHT - 1)
	&& map[pos + WIDTH].team == 0)
		return (pos + WIDTH);
	if (direction == 1 && coords[0] > 0 && map[pos - 1].team == 0)
		return (pos - 1);
	if (direction == 2 && coords[0] < WIDTH - 1 && map[pos + 1].team == 0)
		return (pos + 1);
	if (direction == 3 && coords[1] > 0 && map[pos - WIDTH].team == 0)
		return (pos - WIDTH);
	return (pos);

}

int move(node_t *map, int pos, ipcs_t *ipcs)
{
	msg_t msg_options;
	ssize_t msg = msgrcv(ipcs->msg_id, &msg_options, sizeof(msg_t),
		map[pos].team, IPC_NOWAIT);
	int move_to;
	int team = map[pos].team;

	if (msg != -1 && msg_options.type == team
	&& msg_options.position >= 0
	&& msg_options.position < HEIGHT * WIDTH){
		move_to = go_to(pos, msg_options.position);
	}
	else if (is_there_more_than_one_team(map) != 0)
		move_to = go_to(pos, find_a_victim(map, pos, ipcs));
	else
		move_to = go_to(pos, HEIGHT * WIDTH / 2 + WIDTH / 2);
	if (map[move_to].team != 0)
		move_to = find_free_case(map, pos);
	map[pos].team = 0;
	map[move_to].team = team;
	return (move_to);
}

int check_around(int *around, int team)
{
	for (size_t i = 0; i < 8; i++){
		if (around[i] > 0 && around[i] != team && around[i] != WALL){
			for (size_t j = i + 1; j < 8; j++){
				if (around[j] == around[i]){
					return (1);
				}
			}
		}
	}
	return (0);
}

int     is_alive2(node_t *map, int pos, int *sides)
{
	((pos + WIDTH - 1) >= HEIGHT * WIDTH) ? (sides[3] = 0):
		(sides[3] = map[pos + WIDTH - 1].team);
	((pos - 1) <= 0) ? (sides[4] = 0) : (sides[4] = map[pos - 1].team);
	((pos - WIDTH - 1) <= 0) ? (sides[5] = 0) :
		(sides[5] = map[pos - WIDTH - 1].team);
	((pos - WIDTH) <= 0) ? (sides[6] = 0) :
		(sides[6] = map[pos - WIDTH].team);
	((pos - WIDTH + 1) <= 0) ? (sides[7] = 0) :
		(sides[7] = map[pos - WIDTH + 1].team);
	return (0);
}

int is_alive(node_t *map, int pos)
{
	int *sides;
	int killed = 0;

	sides = malloc(9 * sizeof(int));
	if (!sides)
		return (-1);
	((pos + 1) >= HEIGHT * WIDTH) ? (sides[0] = 0) :
		(sides[0] = map[pos + 1].team);
	((pos + WIDTH + 1) >= HEIGHT * WIDTH) ? (sides[1] = 0) :
		(sides[1] = map[pos + WIDTH + 1].team);
	((pos + WIDTH) >= HEIGHT * WIDTH) ? (sides[2] = 0) :
		(sides[2] = map[pos + WIDTH].team);
	is_alive2(map, pos, sides);
	sides[8] = 0;
	killed = check_around(sides, map[pos].team);
	if (killed == 1){
		map[pos].team = 0;
		return (0);
	}
	return (1);
}
