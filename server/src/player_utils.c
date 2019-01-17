/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** players utils
*/

#include "server.h"
#include <string.h>
#include <stdlib.h>

t_map *get_pcase(t_player *player, t_server *server)
{
	int i = 0;
	t_map **map = server->planete;

	while (map[i]) {
		if (map[i]->pos.x == player->pos.x &&
		map[i]->pos.y == player->pos.y)
			return (map[i]);
		i++;
	}
	return (NULL);
}

t_team *get_pteam(t_player *player, t_server *server)
{
	int i = 0;

	while (server->team[i]) {
		if (strcmp(player->team_name, server->team[i]->team_name) == 0)
			return (server->team[i]);
		i++;
	}
	return (NULL);
}

void	add_word(t_word *word, char *new)
{
	int	a = 0;

	word->str = realloc(word->str, word->i + strlen(new) + 1);
	while (new[a]){
		word->str[word->i++] = new[a++];
	}
}

t_word	*set_word(void)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (word == NULL)
		exit(84);
	word->i = 0;
	word->str = malloc(1);
	return (word);
}
