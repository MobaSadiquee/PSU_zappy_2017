/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Commands
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

void free_players(t_player *head)
{
	t_player *tmp;

	while (head) {
		tmp = head;
		head = head->next;
		if (tmp->team_name)
			free(tmp->team_name);
		free(tmp);
	}
}

void add_player(t_player** head, int sock, t_server *server)
{
	t_player* new_node = new_player(sock);

	if (new_node == NULL)
		return;
	if (!(*head)) {
		new_node->next = NULL;
		(*head) = new_node;
	}
	else {
		new_node->next = (*head);
		(*head) = new_node;
	}
	new_node->pos.x = rand() % server->width;
	new_node->pos.y = rand() % server->height;
}

t_player *search_player(t_player *head, int sock)
{
	t_player *current_node = head;

	while (current_node) {
		if (current_node->sock == sock)
			return (current_node);
		current_node = current_node->next;
	}
	return (NULL);
}

void remove_player(t_player** head, int sock)
{
	t_player* current_node = (*head);
	t_player* prev_node = current_node;

	if ((*head)->sock == sock) {
		(*head) = (*head)->next;
		return;
	}
	while (current_node) {
		if (current_node->sock == sock) {
			prev_node->next = current_node->next;
		}
		prev_node = current_node;
		current_node = current_node->next;
	}
}

int get_team_count(t_player* head, char *team_name)
{
	int count = 0;
	t_player *current_node = head;

	while (current_node) {
		if (current_node->team_name
		&& strcmp(current_node->team_name, team_name) == 0)
			count++;
		current_node = current_node->next;
	}
	return (count);
}
