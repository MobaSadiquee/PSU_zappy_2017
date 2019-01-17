/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Commands
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <string.h>
#include "server.h"

void use_food(t_server *server)
{
	t_player *tmp = server->players;

	while (tmp) {
		if (tmp->team_name != NULL) {
			tmp->inv[FOOD]--;
		}
		if (tmp->inv[FOOD] <= 0 &&
		strcmp(tmp->team_name, "spectator") != 0) {
			dprintf(tmp->sock, "dead\n");
			FD_CLR(tmp->sock, &server->master);
			shutdown(tmp->sock, SHUT_RDWR);
			close(tmp->sock);
			remove_player(&server->players, tmp->sock);
		}
		tmp = tmp->next;
	}
}

void food_tick(t_server *server)
{
	static struct timeval tv = {0};
	struct timeval tv_cur;

	gettimeofday(&tv_cur, NULL);
	double test = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	double test2 = (tv_cur.tv_sec) * 1000 + (tv_cur.tv_usec) / 1000;
	if (test <= 0.f)
		gettimeofday(&tv, NULL);
	else {
		if ((test2 - test) / 1000 >= 126.f / server->freq) {
			use_food(server);
			gettimeofday(&tv, NULL);
		}
	}
}
