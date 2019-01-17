/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** checking entring parameter
*/

#include "server.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

t_params	func[7] = {
	{"-p", check_port},
	{"-x", check_width},
	{"-y", check_height},
	{"-n", check_names},
	{"-c", check_nb},
	{"-f", check_freq},
	{"-help", help}
};

void	check_port(char **av, int i, t_server *server)
{
	if (av[i + 1] != NULL){
		server->port = atoi(av[i+1]);
		if (server->port <= 0){
			dprintf(2, "Port number entered is erroned\n");
			exit(84);
		}
	}
}

void	check_width(char **av, int i, t_server *server)
{
	if (av[i + 1] != NULL){
		server->width = atoi(av[i+1]);
		if (server->width <= 1){
			dprintf(2, "Width number entered is too low\n");
			exit(84);
		}
	}
}

void	check_height(char **av, int i, t_server *server)
{
	if (av[i + 1] != NULL){
		server->height = atoi(av[i+1]);
		if (server->height <= 1){
			dprintf(2, "Height number entered is too low\n");
			exit(84);
		}
	}
}

void	check_nb(char **av, int i, t_server *server)
{
	int	a = 0;

	if (av[i + 1] != NULL){
		server->team_max = atoi(av[i+1]);
		if (server->team_max <= 0){
			dprintf(2, "clientsNb number entered is too low\n");
			exit(84);
		}
	}
	if (server->team != NULL){
		while (server->team[a])
			server->team[a++]->team_max = server->team_max;
	}
}

void	check_params(int ac, char **av, t_server *server)
{
	int	i = 1;
	int	a = 0;

	while (i < ac){
		while (a < 7){
			if (strcmp(av[i], func[a].cmd) == 0)
				func[a].cmd_func(av, i, server);
			a++;
		}
		i++;
		a = 0;
	}
}
