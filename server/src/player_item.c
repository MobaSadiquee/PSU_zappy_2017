/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** file for player interaction with item on the map and elevation
*/

#include "server.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

t_ressources	ress[7] = {
	{"linemate"},
	{"deraumere"},
	{"sibur"},
	{"mendiane"},
	{"phiras"},
	{"thystame"},
	{"food"}
};

int	which_item(int sock, char *m)
{
	int	i = 0;

	while (i < 7){
		if (strcmp(m, ress[i].name) == 0)
			break ;
		i++;
	}
	if (i == 7){
		dprintf(sock, "ko\n");
		return (-1);
	}
	return (i);
}

void	take_object(int sock, t_server *server, char *args)
{
	int	i = which_item(sock, args);
	int	a = 0;
	t_player	*player = search_player(server->players, sock);

	if (i == -1)
		return ;
	while (server->planete[a]){
		if (server->planete[a]->pos.x == player->pos.x &&
		server->planete[a]->pos.y == player->pos.y)
			break ;
		a++;
	}
	if (server->planete[a]->objects[i] == 0)
		dprintf(sock, "ko\n");
	else {
		server->planete[a]->objects[i]--;
		player->inv[i]++;
		dprintf(player->sock, "ok\n");
	}
}

void	drop_object(int sock, t_server *server, char *args)
{
	int	i = which_item(sock, args);
	int	a = 0;
	t_player	*player = search_player(server->players, sock);

	if (i == -1)
		return ;
	while (server->planete[a]){
		if (server->planete[a]->pos.x == player->pos.x &&
		server->planete[a]->pos.y == player->pos.y)
			break ;
		a++;
	}
	if (player->inv[i] == 0)
		dprintf(sock, "ko\n");
	else {
		server->planete[a]->objects[i]++;
		player->inv[i]--;
		dprintf(player->sock, "ok\n");
	}
}

void	set_ears(t_server *server)
{
	t_player	*temp = server->players;

	while (temp != NULL) {
		temp->ears = 0;
		temp = temp->next;
	}
}

void	check_origin(t_server *server, t_pos pos, char *mess)
{
	t_player *temp = server->players;

	while (temp != NULL) {
		if (temp->pos.x == pos.x && temp->pos.y == pos.y
		&& temp->ears == 0){
			dprintf(temp->sock, "message 0, %s", mess);
			temp->ears = 1;
		}
		temp = temp->next;
	}
}
