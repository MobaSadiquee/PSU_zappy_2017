/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** second part to broadcast command
*/

#include "server.h"
#include <stdio.h>

t_facing facing[4] = {{NORTH, facing_north}, {SOUTH, facing_south},
			{EAST, facing_east}, {WEST, facing_west}};

void	facing_north(int sock, direction dir, char *mess)
{
	switch (dir) {
	case NORTH:
		dprintf(sock, "message %d, %s\n", 5, mess);
		break;
	case SOUTH:
		dprintf(sock, "message %d, %s\n", 1, mess);
		break;
	case EAST:
		dprintf(sock, "message %d, %s\n", 7, mess);
		break;
	case WEST:
		dprintf(sock, "message %d, %s\n", 3, mess);
		break;
	default:
		break;
	}
}

void	facing_south(int sock, direction dir, char *mess)
{
	switch (dir) {
	case NORTH:
		dprintf(sock, "message %d, %s\n", 1, mess);
		break;
	case SOUTH:
		dprintf(sock, "message %d, %s\n", 5, mess);
		break;
	case EAST:
		dprintf(sock, "message %d, %s\n", 3, mess);
		break;
	case WEST:
		dprintf(sock, "message %d, %s\n", 7, mess);
		break;
	default:
		break;
	}
}

void	facing_east(int sock, direction dir, char *mess)
{
	switch (dir) {
	case NORTH:
		dprintf(sock, "message %d, %s\n", 3, mess);
		break;
	case SOUTH:
		dprintf(sock, "message %d, %s\n", 7, mess);
		break;
	case EAST:
		dprintf(sock, "message %d, %s\n", 1, mess);
		break;
	case WEST:
		dprintf(sock, "message %d, %s\n", 5, mess);
		break;
	default:
		break;
	}
}

void	facing_west(int sock, direction dir, char *mess)
{
	switch (dir) {
	case NORTH:
		dprintf(sock, "message %d, %s\n", 7, mess);
		break;
	case SOUTH:
		dprintf(sock, "message %d, %s\n", 3, mess);
		break;
	case EAST:
		dprintf(sock, "message %d, %s\n", 5, mess);
		break;
	case  WEST:
		dprintf(sock, "message %d, %s\n", 1, mess);
		break;
	default:
		break;
	}
}

void    check_pressence(t_server *server, direction dir, t_pos pos, char *mes)
{
	t_player *temp = server->players;
	int i = 0;

	while (temp != NULL) {
		if (temp->pos.x == pos.x && temp->pos.y == pos.y
		&& temp->ears == 0) {
			while (i < 4) {
				if (temp->dir == facing[i].dir) {
					facing[i].cmd_func(temp->sock,
					dir, mes);
					temp->ears = 1;
				}
				i++;
			}
		}
		temp = temp->next;
		i = 0;
	}
}
