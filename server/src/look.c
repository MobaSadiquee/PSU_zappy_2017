/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** the look function in different direction
*/

#include "server.h"
#include <stdlib.h>
#include <stdio.h>

t_looking	direct[4] = {
	{NORTH, look_north},
	{EAST, look_east},
	{SOUTH, look_south},
	{WEST, look_west}
};

void look_north(t_server *server, t_player *player, int *ac, t_word *word)
{
	int	i = 0;
	int	x = player->pos.x + ac[1];
	int	y = player->pos.y - (ac[0] + 1);

	while (x < 0)
		x += server->width;
	while (y < 0)
		y += server->height;
	while (server->planete[i]) {
		if (server->planete[i]->pos.x == x &&
		server->planete[i]->pos.y == y) {
			get_ressources(server->planete[i], player->sock,
			server, word);
			break;
		}
		i++;
	}
}

void look_south(t_server *server, t_player *player, int *ac, t_word *word)
{
	int	i = server->width * server->height - 1;
	int	x = player->pos.x - ac[1];
	int	y = player->pos.y - (ac[0] - 1);

	while (x < 0)
		x += server->width;
	while (y < 0)
		y += server->height;
	while (i >= 0) {
		if (server->planete[i]->pos.x == x &&
		server->planete[i]->pos.y == y) {
			get_ressources(server->planete[i], player->sock,
			server, word);
			break;
		}
		i--;
	}
}

void look_east(t_server *server, t_player *player, int *ac, t_word *word)
{
	int	i = server->width * server->height - 1;
	int	x = player->pos.x - (ac[0] + 1);
	int	y = player->pos.y - ac[1];

	while (x < 0)
		x += server->width;
	while (y < 0)
		y += server->height;
	while (i >= 0) {
		if (server->planete[i]->pos.x == x &&
		server->planete[i]->pos.y == y) {
			get_ressources(server->planete[i], player->sock,
			server, word);
			break;
		}
		i--;
	}
}

void look_west(t_server *server, t_player *player, int *ac, t_word *word)
{
	int	i = 0;
	int	x = player->pos.x + (ac[0] + 1);
	int	y = player->pos.y + ac[1];

	while (x < 0)
		x += server->width;
	while (y < 0)
		y += server->height;
	while (server->planete[i]) {
		if (server->planete[i]->pos.x == x &&
		server->planete[i]->pos.y == y) {
			get_ressources(server->planete[i], player->sock,
			server, word);
			break;
		}
		i++;
	}
}

void look(int sock, t_server *server)
{
	int i = 0;
	int ac[2];
	t_player *player = search_player(server->players, sock);
	t_word *word = set_word();

	ac[0] = 0;
	look_self(server, player, word);
	while (ac[0] < player->level) {
		ac[1] = -ac[0] - 1;
		while (ac[1] < ac[0] + 2) {
			add_word(word, ", ");
			while (i < 4){
				if (player->dir == direct[i].dir)
					direct[i].cmd_func(server,
					player, ac, word);
				i++;
			}
			ac[1]++;
			i = 0;
		}
		ac[0]++;
	}
	word->str[word->i] = '\0';
	if (word->str[word->i - 1] == ' ')
		dprintf(sock, "[ %s]\n", word->str);
	else
		dprintf(sock, "[ %s ]\n", word->str);
	free(word->str);
	free(word);
}
