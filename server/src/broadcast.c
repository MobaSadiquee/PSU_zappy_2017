/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** broadcast file
*/

#include "server.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void broadcast_north(t_server *server, t_player *player, int *ac, char *mess)
{
	int i = 0;
	int x = player->pos.x + ac[1];
	int y = player->pos.y - (ac[0] + 1);

	while (x < 0)
		x += server->width;
	while (y < 0)
		y += server->height;
	while (server->planete[i]) {
		if (server->planete[i]->pos.x == x &&
		server->planete[i]->pos.y == y) {
			check_pressence(server, NORTH,
					server->planete[i]->pos, mess);
			break;
		}
		i++;
	}
}

void broadcast_south(t_server *server, t_player *player, int *ac, char *mess)
{
	int i = server->width * server->height - 1;
	int x = player->pos.x - ac[1];
	int y = player->pos.y - (ac[0] - 1);

	while (x < 0)
		x += server->width;
	while (y < 0)
		y += server->height;
	while (i >= 0) {
		if (server->planete[i]->pos.x == x &&
		server->planete[i]->pos.y == y) {
			check_pressence(server, SOUTH,
					server->planete[i]->pos, mess);
			break;
		}
		i--;
	}
}

void broadcast_east(t_server *server, t_player *player, int *ac, char *mess)
{
	int i = server->width * server->height - 1;
	int x = player->pos.x - (ac[0] + 1);
	int y = player->pos.y - ac[1];

	while (x < 0)
		x += server->width;
	while (y < 0)
		y += server->height;
	while (i >= 0) {
		if (server->planete[i]->pos.x == x &&
		server->planete[i]->pos.y == y) {
			check_pressence(server, EAST,
					server->planete[i]->pos, mess);
			break;
		}
		i--;
	}
}

void broadcast_west(t_server *server, t_player *player, int *ac, char *mess)
{
	int i = 0;
	int x = player->pos.x + (ac[0] + 1);
	int y = player->pos.y + ac[1];

	while (x < 0)
		x += server->width;
	while (y < 0)
		y += server->height;
	while (server->planete[i]) {
		if (server->planete[i]->pos.x == x &&
		server->planete[i]->pos.y == y) {
			check_pressence(server, WEST,
					server->planete[i]->pos, mess);
			break;
		}
		i++;
	}
}

void broadcast(int sock, t_server *server, char *m)
{
	int ac[2];
	t_player *player = search_player(server->players, sock);

	ac[0] = 0;
	ac[1] = 0;
	player->ears = 1;
	check_origin(server, player->pos, m);
	while (ac[0] < sqrt(server->width*server->height)) {
		ac[1] = -ac[0] - 1;
		while (ac[1] < ac[0] + 2) {
			broadcast_s(server, player, ac, m);
			ac[1]++;
		}
		ac[0]++;
	}
	set_ears(server);
	dprintf(sock, "ok\n");
}
