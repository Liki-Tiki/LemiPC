/*
** EPITECH PROJECT, 2018
** Project
** File description:
** sem.c
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

void	lock_sem(int sem_id)
{
	struct sembuf	sem;

	sem.sem_num = 0;
	sem.sem_flg = 0;
	sem.sem_op = -1;
	semop(sem_id, &sem, 1);
}

void	unlock_sem(int sem_id)
{
	struct sembuf	sem;

	sem.sem_num = 0;
	sem.sem_flg = 0;
	sem.sem_op = 1;
	semop(sem_id, &sem, 1);
}

ipcs_t *init(char *path)
{
	ipcs_t *temp;

	temp = malloc(sizeof(ipcs_t));
	if (!temp)
		return (NULL);
	temp->msg_id = 0;
	temp->sem_id = 0;
	temp->shm_id = 0;
	temp->key = ftok(path, 0);
	if (temp->key == -1){
		fprintf(stderr, "Wrong path\n");
		return (NULL);
	}
	return (temp);
}
