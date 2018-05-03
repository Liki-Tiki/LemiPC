/*
** EPITECH PROJECT, 2018
** dispd
** File description:
** disp
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include "lemipc.h"

int is_there_more_than_one_team(node_t *map)
{
	int tmp = map[0].team;

	for (size_t i = 0; i < HEIGHT * WIDTH; i++)
	{
		if (map[i].team != 0 &&
		(tmp == 0 || tmp == WALL) && map[i].team != WALL)
			tmp = map[i].team;
		else if (map[i].team != 0 &&
		tmp != map[i].team &&
		tmp != 0 && map[i].team != WALL && tmp != WALL)
			return (1);
	}
	return (0);
}

void print_limit(void)
{
	printf(BACKGROUND_WHITE " " COLOR_RESET);
	for (size_t i = 0; i < WIDTH; i++)
	{
		printf(BACKGROUND_WHITE " " COLOR_RESET);
	}
	printf(BACKGROUND_WHITE" \n" COLOR_RESET);
}

void print_soldier(int soldier)
{
	char *colors[] = {
		COLOR_RED,
		COLOR_GREEN,
		COLOR_YELLOW,
		COLOR_BLUE,
		COLOR_MAGENTA,
		COLOR_CYAN,
		COLOR_RED_BRIGHT,
		COLOR_GREEN_BRIGHT,
		COLOR_YELLOW_BRIGHT,
		COLOR_BLUE_BRIGHT,
		COLOR_MAGENTA_BRIGHT,
		COLOR_CYAN
	};
	printf("%s%c"COLOR_RESET, colors[soldier % 11], ((('!' + (15 + soldier))
		% 130)));
}

void print_map(node_t *map)
{

	print_limit();
	for (int i = 0; i < HEIGHT * WIDTH; i++)
	{
		if ((i) % WIDTH == 0)
			printf(BACKGROUND_WHITE " " COLOR_RESET);
		if (map[i].team == WALL){
			printf(BACKGROUND_WHITE " " COLOR_RESET);
		} else if (map[i].team > 0 && map[i].team != WALL){
			print_soldier(map[i].team);
		}
		else
			printf(" ");
		if ((i + 1) % WIDTH == 0)
			printf(BACKGROUND_WHITE         " \n" COLOR_RESET);
	}
	print_limit();
}

int get_alive_by_team(node_t *map, int team)
{
	int nb = 0;

	for (int i = 0; i < HEIGHT * WIDTH; i++){
		if (map[i].team == team)
			nb++;
	}
	return (nb);
}
