/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** inventory
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

void print_inv_ressources(int amount, char *ressources, t_word *word)
{
	char buffer[10];

	snprintf(buffer, 10, "%d", amount);
	add_word(word, ressources);
	add_word(word, " ");
	add_word(word, buffer);
	if (strcmp(ressources, "thystame") == 0)
		add_word(word, " ");
	else
		add_word(word, ", ");
}

void get_inv_ressources_second(t_player *npc, int i, t_word *word)
{
	switch (i) {
	case 0 : print_inv_ressources(npc->inv[i], "linemate", word);
		break;
	case 1 : print_inv_ressources(npc->inv[i], "deraumere", word);
		break;
	case 2 : print_inv_ressources(npc->inv[i], "sibur", word);
		break;
	case 3 : print_inv_ressources(npc->inv[i], "mendiane", word);
		break;
	case 4 : print_inv_ressources(npc->inv[i], "phiras", word);
		break;
	case 5 : print_inv_ressources(npc->inv[i], "thystame", word);
		break;
	case 6 : print_inv_ressources(npc->inv[i], "food", word);
	}
}

int get_inv_ressources(t_player *npc, t_word *word)
{
	int i = 0;

	add_word(word, "[ ");
	if (npc->inv[6] > 0)
		get_inv_ressources_second(npc, 6, word);
	while (i < 6) {
		get_inv_ressources_second(npc, i, word);
		i++;
	}
	add_word(word, "]\n");
	return (0);
}

void check_inventory(int sock, t_server *server)
{
	t_player *npc = search_player(server->players, sock);
	t_word	*word = set_word();

	get_inv_ressources(npc, word);
	word->str[word->i] = '\0';
	dprintf(sock, "%s", word->str);
	free(word->str);
	free(word);
}
