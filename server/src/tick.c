/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Commands
*/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include "server.h"

void stack_tick_check(t_cmd *tmp_cmd, t_player *tmp, t_server *server)
{
	struct timeval res;
	double test;
	double test2;
	double test3;

	gettimeofday(&res, NULL);
	test = (res.tv_sec) * 1000 + (res.tv_usec) / 1000;
	test2 = (tmp->cmd_stack.time.tv_sec) * 1000 +
	(tmp->cmd_stack.time.tv_usec) / 1000;
	test3 = tmp_cmd->time / server->freq;
	if ((test - test2) / 1000 >= test3) {
		tmp_cmd->ptr(tmp->sock, server, tmp->cmd_stack.top->args);
		stack_pop(&tmp->cmd_stack);
	}
}

void stack_tick(t_server *server)
{
	t_cmd *tmp_cmd = NULL;
	t_player *tmp = server->players;

	while (tmp) {
		if (tmp->cmd_stack.top)
			tmp_cmd = tmp->cmd_stack.top->cmd;
		else
			tmp_cmd = NULL;
		if (tmp_cmd) {
			stack_tick_check(tmp_cmd, tmp, server);
		}
		tmp = tmp->next;
	}
}

void check_sock(int i, int sock, fd_set *read_set, t_server *server)
{
	if (FD_ISSET(i, read_set)) {
		if (i == sock) {
			int new = accept(sock, NULL, 0);
			FD_SET(new, &server->master);
			add_player(&server->players, new, server);
			dprintf(new, "WELCOME\n");
			printf("New client incoming\n");
		}
		else {
			if (search_player(server->players, i) != NULL &&
			search_player(server->players, i)->team_name == NULL)
				initialize_player_team(i, server);
			else {
				handle_cmd(i, server);
			}
		}
	}
}
