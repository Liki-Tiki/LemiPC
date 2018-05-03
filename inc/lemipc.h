/*
** EPITECH PROJECT, 2018
** Project
** File description:
** lemipc.h
*/

#ifndef PROJECT_LEMIPC_H
#define PROJECT_LEMIPC_H

# include <sys/types.h>
# include <sys/ipc.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RED_BRIGHT		"\x1b[91m"
#define COLOR_GREEN_BRIGHT		"\x1b[92m"
#define COLOR_YELLOW_BRIGHT		"\x1b[93m"
#define COLOR_BLUE_BRIGHT		"\x1b[94m"
#define COLOR_MAGENTA_BRIGHT		"\x1b[95m"
#define COLOR_CYAN_BRIGHT		"\x1b[96m"
#define BACKGROUND_WHITE		"\x1b[47m"
#define COLOR_RESET   "\x1b[0m"

#define WIDTH (80)
#define HEIGHT (50)

#define WALL (994)

typedef struct infos_s
{
	int amount;
	int fail;
	int *teams;
	int *teams2;
	int *team_alive;
	int stock;
} infos_t;

typedef struct node_s
{
	int team;
} node_t;

typedef struct ipcs_s
{
	key_t key;
	int shm_id;
	int sem_id;
	int msg_id;
} ipcs_t;

typedef struct msg_s
{
	long type;
	int position;
} msg_t;

void print_soldier(int soldier);
int is_there_more_than_one_team(node_t *map);
int	nbr_alive(node_t *map);
ipcs_t *init(char *path);
int find_free_case(node_t *map, int pos);
int move(node_t *, int, ipcs_t *);
int init_server(ipcs_t *ipcs, char **av);
int init_client(ipcs_t *ipcs, int team);
void lock_sem(int sem_id);
int *get_xy(int);
int distance(int, int);
int is_there_more_than_one_team(node_t *map);
void print_limit(void);
void print_soldier(int soldier);
void print_map(node_t *);
int get_alive_by_team(node_t *, int);
int go_to(int, int);
int is_alive(node_t *, int);
int find_a_victim(node_t *, int pos, ipcs_t *);
void unlock_sem(int sem_id);
int fight(node_t *map, ipcs_t *ipcs, int pos);
void display_map(node_t *map, ipcs_t *ipcs);

#endif //PROJECT_LEMIPC_H
