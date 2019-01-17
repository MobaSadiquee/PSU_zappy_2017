/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** the fork function command
*/

#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

void	new_max_team(t_eggs *eggs, t_server *server)
{
	int	i = 0;

	while (server->team[i]){
		if (strcmp(server->team[i]->team_name, eggs->team_name) == 0)
			server->team[i]->team_max++;
		i++;
	}
}

void	egg_on_case(t_map *map, t_server *server, t_word *word)
{
	t_eggs	*egg = server->eggs;

	while (egg != NULL){
		if (egg->pos.x == map->pos.x &&
		egg->pos.y == map->pos.y)
			add_word(word, "egg ");
		egg = egg->next;
	}
}

void	fork_player(int sock, t_server *server)
{
	t_eggs	*new;
	t_player *player = search_player(server->players, sock);

	new = malloc(sizeof(t_eggs));
	if (new == NULL)
		exit(84);
	new->pos.x = player->pos.x;
	new->pos.y = player->pos.y;
	new->team_name = strdup(player->team_name);
	gettimeofday(&new->time, NULL);
	new->next = NULL;
	if (server->eggs == NULL)
		server->eggs = new;
	else {
		while (server->eggs->next != NULL)
			server->eggs = server->eggs->next;
		server->eggs->next = new;
	}
	dprintf(sock , "ok\n");
}

void eggs_tick(t_server *server)
{
	double test;
	double test2;
	t_eggs *tmp = server->eggs;
	struct timeval tv_cur;

	while (tmp) {
		gettimeofday(&tv_cur, NULL);
		test = (tmp->time.tv_sec) * 1000 + (tmp->time.tv_usec) / 1000;
		test2 = (tv_cur.tv_sec) * 1000 + (tv_cur.tv_usec) / 1000;
		if ((test2 - test) / 1000 >= 600.f / server->freq) {
			new_max_team(tmp, server);
			eclosion(server, tmp);
		}
		tmp = tmp->next;
	}
}

void	eclosion(t_server *server, t_eggs *egg)
{
	t_eggs	*temp = server->eggs;

	if (temp == egg){
		server->eggs = temp->next;
		free(egg->team_name);
		free(egg);
	}
	while (temp->next != NULL){
		if (temp->next == egg){
			temp->next = egg->next;
			free(egg->team_name);
			free(egg);
		}
		temp = temp->next;
	}
}
