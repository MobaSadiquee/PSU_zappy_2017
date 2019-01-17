/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Commands
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/time.h>
#include "server.h"

static t_cmd cmd_list[] =
			{{"Look", 7, &look}, {"Inventory", 1, &check_inventory},
			{"Forward", 7, &move_player}, {"Left", 7, &turn_left},
			{"Right", 7, &turn_right},
			{"Connect_nbr", 0, &connect_nbr},
			{"Broadcast", 7, &broadcast},
			{"Incantation", 300, &do_elevation},
			{"Take", 7, &take_object}, {"Set", 7, &drop_object},
			{"Map", 0, &item_on_case}, {"Players", 0, &get_players},
			{"Fork", 42, &fork_player}, {"Eject", 7, &ejection}};

void process(char *cmd, int sock, t_server *server)
{
	char *token = NULL;
	t_player *tmp = search_player(server->players, sock);

	printf("[Sock #%d] : %s\n", sock, cmd);
	token = strtok(cmd, "\r \n");
	for (int i = 0; i < 14; i++) {
		if (token && strcmp(token, cmd_list[i].name) == 0) {
			if (strcmp(token, "Incantation") == 0
			&& incantation(token, sock, server) == 1)
				stack_push(&tmp->cmd_stack,
				&cmd_list[i], strtok(NULL, " "));
			else if (strcmp(token, "Incantation") != 0)
				stack_push(&tmp->cmd_stack,
				&cmd_list[i], strtok(NULL, " "));
			break;
		}
	}
	free(cmd);
}

void handle_cmd(int sock, t_server *server)
{
	int cnt = 0;
	char str[4000] = {0};
	char *old = str;

	cnt = read(sock, &str, 4000);
	while (cnt > 0)  {
		int res = strchr(old, '\n') - old;
		process(strndup(old, res), sock, server);
		old += res + 1;
		cnt -= res + 1;
	}
}

int create_sock(int port)
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;
	int opt = 1;

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(port);
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR |
		SO_REUSEPORT, &opt, sizeof(opt));
	bind(server_fd, (struct sockaddr*)&address, sizeof(address));
	return (server_fd);
}

void run(t_server *server, int sock)
{
	struct timeval tv = {0, 0};
	fd_set read_set;

	listen(sock, 10);
	FD_ZERO(&server->master);
	FD_SET(sock, &server->master);
	while (1) {
		read_set = server->master;
		tv.tv_sec = 0.2f;
		if (select(FD_SETSIZE, &read_set, NULL, NULL, &tv) == -1) {
			break;
		}
		for (int i = 0; i < FD_SETSIZE; i++) {
			check_sock(i, sock, &read_set, server);
		}
		stack_tick(server);
		food_tick(server);
		eggs_tick(server);
	}
}
