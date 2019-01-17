/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** ejection
*/

#include <stdio.h>
#include "server.h"

void dir_eject(t_server *server, t_player* npc, direction dir)
{
	if (dir == 0)
		dir_eject_north(server, npc);
	if (dir == 1)
		dir_eject_east(server, npc);
	if (dir == 2)
		dir_eject_south(server, npc);
	if (dir == 3)
		dir_eject_west(server, npc);
}

int pos_equal(t_pos first, t_pos second)
{
	if (first.x == second.x) {
		if (first.y == second.y)
			return (1);
	}
	else
		return (0);
	return (0);
}

int eject(t_server *server, t_player *npc, int sock)
{
	int count = 0;
	int pos_total = 0;
	t_player	*temp = server->players;

	while (temp != NULL) {
		if (sock != temp->sock){
			pos_total = pos_equal(npc->pos, temp->pos);
			if (pos_total == 1) {
				dir_eject(server, temp, npc->dir);
				count++;
			}
		}
		temp = temp->next;
	}
	if (count > 0)
		return (0);
	return (1);
}

void ejection(int sock, t_server *server)
{
	t_player *npc = search_player(server->players, sock);
	int retour = 0;


	if (!npc)
		return;
	retour = eject(server, npc, sock);
	if (retour == 1)
		dprintf(sock, "ko\n");
	else
		dprintf(sock, "ok\n");
}
