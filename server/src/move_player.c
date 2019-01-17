/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** move player
*/

#include <stdio.h>
#include "server.h"

void move_player_north(t_player *npc, t_server *server)
{
	if (npc->pos.y == 0)
		npc->pos.y = server->height - 1;
	else
		npc->pos.y = npc->pos.y - 1;
}

void move_player_south(t_player *npc, t_server *server)
{
	if (npc->pos.y == server->height - 1)
		npc->pos.y = 0;
	else
		npc->pos.y = npc->pos.y + 1;
}

void move_player_east(t_player *npc, t_server *server)
{
	if (npc->pos.x == 0)
		npc->pos.x = server->width - 1;
	else
		npc->pos.x = npc->pos.x - 1;
}

void move_player_west(t_player *npc, t_server *server)
{
	if (npc->pos.x == server->width - 1)
		npc->pos.x = 0;
	else
		npc->pos.x = npc->pos.x + 1;
}

void move_player(int sock, t_server *server)
{
	t_player *npc = search_player(server->players, sock);

	if (!npc)
		return;
	if (npc->dir == 0)
		move_player_north(npc, server);
	if (npc->dir == 1)
		move_player_east(npc, server);
	if (npc->dir == 2)
		move_player_south(npc, server);
	if (npc->dir == 3)
		move_player_west(npc, server);
	dprintf(sock, "ok\n");
}
