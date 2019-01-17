/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** ejection direction
*/

#include "server.h"

void dir_eject_north(t_server *server, t_player *npc)
{
	if (npc->pos.y == 0)
		npc->pos.y = server->height - 1;
	else
		npc->pos.y = npc->pos.y - 1;
}

void dir_eject_south(t_server *server, t_player *npc)
{
	if (npc->pos.y == server->height - 1)
		npc->pos.y = 0;
	else
		npc->pos.y = npc->pos.y + 1;
}

void dir_eject_east(t_server *server, t_player *npc)
{
	if (npc->pos.x == 0)
		npc->pos.x = server->width - 1;
	else
		npc->pos.x = npc->pos.x - 1;
}

void dir_eject_west(t_server *server, t_player *npc)
{
	if (npc->pos.x == server->width - 1)
		npc->pos.x = 0;
	else
		npc->pos.x = npc->pos.x + 1;
}
