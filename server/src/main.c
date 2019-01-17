/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** main file for server
*/

#include "server.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void	help(char **av, int i, t_server *server)
{
	av = av;
	i = i;
	server = server;
	printf("USAGE: ./zappy_server -p port -x width -y height -n"
	" name1 name2");
	printf(" ... -c clientsNb -f freq\n");
	printf("\tport\tis the port number\n");
	printf("\twidth\tis the width of the world\n");
	printf("\theight\tis the height of the world\n");
	printf("\tnameX\tis the name of the team X\n");
	printf("\tclientsNb\tis the number of authorized clients per team\n");
	printf("\tfreq\tis the reciprocal of time unit for execution"
	"of actions\n");
	exit(0);
}

int	main(int ac, char **av)
{
	t_server server = {.width = 5, .height = 3, .planete = NULL,
			.players = NULL, .team = NULL, .team_max = 3,
			.freq = 100};

	check_params(ac, av, &server);
	server.planete = create_map(&server);
	if (server.planete == NULL || server.team == NULL)
		help(av, 0, &server);
	run(&server, create_sock(server.port));
}
