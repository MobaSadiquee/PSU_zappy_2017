/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Commands
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

int advance_idx(char *str, char delim)
{
	int i = 0;

	while (str[i] && str[i] != delim) {
		i++;
	}
	return (i + 1);
}

void append_item(int j, int quantity, char *to_append)
{
	char items[7][30] = {"Linemate", "Deraumere", "Sibur",
	"Mendiane", "Phiras", "Thystame", "Food"};

	sprintf(to_append, "%s%s %d\n", to_append, items[j], quantity);
}

void item_on_case(int sock, t_server *server, char *args)
{
	int i = 0;
	int j = 0;
	t_map **tmp = server->planete;
	char response[2048] = {0};

	while (tmp[i]) {
		if (tmp[i]->pos.x == atoi(args)
		&& tmp[i]->pos.y == atoi(args + advance_idx(args, '/'))) {
			while (j < 7) {
				append_item(j, tmp[i]->objects[j], response);
				j++;
			}
			break;
		}
		i++;
	}
	dprintf(sock, "%s", response);
}

int get_team_nbr(char *team_name, t_server *server)
{
	int i = 0;

	while (server->team[i]) {
		if (strcmp(team_name, server->team[i]->team_name) == 0)
			return (i);
		i++;
	}
	return (i);
}

void get_players(int sock, t_server *server)
{
	int count = 0;
	char response[2048] = {0};
	t_player *tmp = server->players;

	while (tmp) {
		if (tmp->team_name && strcmp(tmp->team_name, "spectator") != 0) {
			sprintf(response, "%s%d %d %d %d %d\n", response,
			get_team_nbr(tmp->team_name, server),
			tmp->pos.x, tmp->pos.y, tmp->dir, tmp->level);
			count++;
		}
		tmp = tmp->next;
	}
	if (count > 0)
		dprintf(sock, "%s", response);
	else
		dprintf(sock, "No Players\n");
}
