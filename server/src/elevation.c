/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Commands
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

void do_elevation(int sock, t_server *server)
{
	t_player *tmp = server->players;
	t_player *player = search_player(server->players, sock);

	while (tmp) {
		if (tmp->pos.x == player->pos.x &&
		tmp->pos.y == player->pos.y) {
			tmp->level++;
			dprintf(tmp->sock, "Current level: %d\n", tmp->level);
		}
		tmp = tmp->next;
	}
}

int check_ressources_1(t_player *player, t_map *cur_case, int count)
{
	if (player->level == 1 &&
	cur_case->objects[LINEMATE] >= 1 && count >= 1)
		return (1);
	if (player->level == 2 && cur_case->objects[LINEMATE] >= 1
	&& cur_case->objects[DERAUMERE] >= 1
	&& cur_case->objects[SIBUR] >= 1 && count >= 2)
		return (1);
	if (player->level == 3 && cur_case->objects[LINEMATE] >= 2
	&& cur_case->objects[SIBUR] >= 1
	&& cur_case->objects[PHIRAS] >= 2 && count >= 2)
		return (1);
	if (player->level == 4 && cur_case->objects[LINEMATE] >= 1
	&& cur_case->objects[DERAUMERE] >= 1 && cur_case->objects[SIBUR] >= 2
	&& cur_case->objects[PHIRAS] >= 1 && count >= 4)
		return (1);
	return (0);
}

int check_ressources_2(t_player *player, t_map *cur_case, int count)
{
	if (player->level == 5 && cur_case->objects[LINEMATE] >= 1
	&& cur_case->objects[DERAUMERE] >= 2 && cur_case->objects[SIBUR] >= 1
	&& cur_case->objects[MENDIANE] >= 3 && count >= 4)
		return (1);
	if (player->level == 6 && cur_case->objects[LINEMATE] >= 1
	&& cur_case->objects[DERAUMERE] >= 2 && cur_case->objects[SIBUR] >= 3
	&& cur_case->objects[PHIRAS] >= 1 && count >= 6)
		return (1);
	if (player->level == 7 && cur_case->objects[LINEMATE] >= 2
	&& cur_case->objects[DERAUMERE] >= 2 && cur_case->objects[SIBUR] >= 2
	&& cur_case->objects[MENDIANE] >= 2 && cur_case->objects[THYSTAME] >= 2
	&& cur_case->objects[THYSTAME] >= 1 && count >= 6)
		return (1);
	return (0);
}

int check_elevation(char *cmd, int sock, t_server *server)
{
	t_player *tmp = server->players;
	t_player *player = search_player(server->players, sock);
	int count = 0;
	t_map *cur_case = get_pcase(player, server);

	if (cmd && strcmp(cmd, "Incantation") != 0)
		return (0);
	while (tmp) {
		if (tmp->pos.x == player->pos.x && tmp->pos.y == player->pos.y
		&& tmp->level == player->level)
			count++;
		tmp = tmp->next;
	}
	if (check_ressources_1(player, cur_case, count) == 1
	|| check_ressources_2(player, cur_case, count) == 1)
		return (1);
	return (0);
}

int incantation(char *cmd, int sock, t_server *server)
{
	t_player *tmp = server->players;
	t_player *player = search_player(server->players, sock);

	if (check_elevation(cmd, sock, server) == 0) {
		dprintf(sock, "ko\n");
		return (0);
	}
	while (tmp) {
		if (tmp->pos.x == player->pos.x &&
		tmp->pos.y == player->pos.y) {
			dprintf(tmp->sock, "Elevation underway\n");
		}
		tmp = tmp->next;
	}
	return (1);
}
