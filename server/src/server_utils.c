/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** server utils
*/

#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

void handle_spec(int sock, t_server *server)
{
	t_player *tmp = search_player(server->players, sock);

	if (tmp) {
		tmp->team_name = strdup("spectator");
		tmp->pos.x = -100;
		tmp->pos.y = -100;
		tmp->inv[FOOD] = -1;
	}
}

int get_team_max(char *team_name, t_server *server)
{
	int i = 0;

	while (server->team[i]) {
		if (strcmp(team_name, server->team[i]->team_name) == 0)
			return server->team[i]->team_max;
		i++;
	}
	return (0);
}

void init_player_check(int sock, char *str, t_server *server, t_player *tmp)
{
	int i = 0;

	while (server->team[i]) {
		if (strcmp(str, server->team[i]->team_name) == 0
		&& get_team_count(server->players, str)
		< get_team_max(str, server)) {
			tmp->team_name = strdup(server->team[i]->team_name);
			dprintf(sock, "%d\n", get_team_max(str, server)
			- get_team_count(server->players, str));
			dprintf(sock, "%d %d\n", server->width, server->height);
			break;
		}
		i++;
	}
}

void initialize_player_team(int sock, t_server *server)
{
	char str[4000] = {0};
	t_player *tmp = search_player(server->players, sock);

	if (tmp != NULL) {
		int test = read(sock, &str, 4000);
		str[test - 1] = '\0';
		if (strcmp(str, "spectator") == 0) {
			handle_spec(sock, server);
			return;
		}
		init_player_check(sock, str, server, tmp);
		if (tmp->team_name == NULL) {
			remove_player(&server->players, sock);
			FD_CLR(sock, &server->master);
			shutdown(sock, SHUT_RDWR);
			close(sock);
		}
	}
}
