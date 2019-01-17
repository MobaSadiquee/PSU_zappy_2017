/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** look return functions
*/

#include <stdio.h>
#include "server.h"

void print_ressources(char *ressources, t_word *word)
{
	add_word(word, ressources);
}

void get_ressources2(int i, t_word *word)
{
	switch (i) {
	case 0 : print_ressources("linemate", word);
	break;
	case 1 : print_ressources("deraumere", word);
	break;
	case 2 : print_ressources("sibur", word);
	break;
	case 3 : print_ressources("mendiane", word);
	break;
	case 4 : print_ressources("phiras", word);
	break;
	case 5 : print_ressources("thystame", word);
	break;
	case 6 : print_ressources("food", word);
	}
}

void	players_on_case(t_map *square, t_server *server, t_word *word)
{
	t_player	*player = server->players;

	while (player != NULL){
		if (player->pos.x == square->pos.x &&
		player->pos.y == square->pos.y){
			add_word(word, "player ");
		}
		player = player->next;
	}
}

int get_ressources(t_map *square, int sock, t_server *server, t_word *word)
{
	int i = 0;
	int a = 0;
	int b = 0;

	sock = sock;
	players_on_case(square, server, word);
	egg_on_case(square, server, word);
	while (i < 7) {
		while (a < square->objects[i]){
			if (b != 0)
				add_word(word, " ");
			get_ressources2(i, word);
			a++;
			b++;
		}
		i++;
		a = 0;
		b++;
	}
	return (0);
}

void	look_self(t_server *server, t_player *player, t_word *word)
{
	int	i = 0;

	while (server->planete[i]){
		if (server->planete[i]->pos.x == player->pos.x &&
		server->planete[i]->pos.y == player->pos.y) {
			get_ressources(server->planete[i],
				player->sock, server, word);
			break;
		}
		i++;
	}
}
