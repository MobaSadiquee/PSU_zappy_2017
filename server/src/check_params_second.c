/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** second file to check params
*/

#include "server.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

t_team	*add_new_team(char *name, int team_max)
{
	t_team	*team;

	team = malloc(sizeof(t_team));
	if (team == NULL)
		exit(84);
	team->team_name = strdup(name);
	team->team_max = team_max;
	team->team_count = 0;
	return (team);
}

void	check_names(char **av, int i, t_server *server)
{
	int	a = i;
	int	b = 0;

	i++;
	while (av[i] != NULL) {
		if (strncmp(av[i], "-", 1) == 0)
			break;
		i++;
	}
	server->team = malloc(sizeof(t_team) * (i - a));
	if (server->team == NULL)
		exit(84);
	while (a < i)
		server->team[b++] = add_new_team(av[a++], server->team_max);
	server->team[b] = NULL;
}

void	check_freq(char **av, int i, t_server *server)
{
	if (av[i + 1] != NULL) {
		server->freq = atoi(av[i+1]);
		if (server->freq <= 0) {
			dprintf(2, "Freq number entered is too low\n");
			exit(84);
		}
	}
}
