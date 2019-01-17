/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** second file for  broadcast function
*/

#include "server.h"

t_broadcasting broad[4] = {{NORTH, broadcast_north}, {EAST, broadcast_east},
			{SOUTH, broadcast_south}, {WEST, broadcast_west}};

void	broadcast_s(t_server *server, t_player *player, int *ac, char *m)
{
	int	i = 0;

	while (i < 4){
		broad[i].cmd_func(server, player, ac, m);
		i++;
	}
}
