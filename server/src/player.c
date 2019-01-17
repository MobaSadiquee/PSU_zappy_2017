/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** diverse function to keep track of the player
*/

#include "server.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	check_team_name(char *name, t_server *server)
{
	int	i = 0;

	while (server->team[i] != NULL){
		if (strcmp(name, server->team[i]->team_name) == 0)
			return (0);
		i++;
	}
	dprintf(2, "This team name doesn't exist\n");
	return (-1);
}

void	connect_nbr(int sock, t_server *server)
{
	int	a = 0;
	t_player *player = search_player(server->players, sock);
	t_player	*temp = server->players;

	while (temp) {
		if (strcmp(temp->team_name, player->team_name) == 0)
			a++;
		temp = temp->next;
	}
	dprintf(sock, "%d\n", get_pteam(player, server)->team_max - a);
}

void	turn_right(int sock, t_server *server)
{
	t_player *player = search_player(server->players, sock);

	if (player->dir == 0)
		player->dir = 3;
	else
		player->dir--;
	dprintf(sock, "ok\n");
}

void	turn_left(int sock, t_server *server)
{
	t_player *player = search_player(server->players, sock);

	player->dir++;
	if (player->dir == 4)
		player->dir = 0;
	dprintf(sock, "ok\n");
}

t_player	*new_player(int sock)
{
	t_player	*new;
	int	i = 0;

	new = malloc(sizeof(t_player));
	if (new == NULL)
		return (NULL);
	new->sock = sock;
	new->team_name = NULL;
	new->dir = rand() % 4;
	new->cmd_stack.top = NULL;
	new->cmd_stack.count = 0;
	new->pos.x = 0;
	new->pos.y = 0;
	new->ears = 0;
	while (i < 6)
		new->inv[i++] = 0;
	new->inv[i] = 10;
	new->level = 1;
	return (new);
}
