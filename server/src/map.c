/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** map
*/

#include "server.h"
#include <stdlib.h>
#include <stdio.h>

t_map	*new_node(int	a, int width)
{
	t_map	*node;
	int	b = 0;

	node = malloc(sizeof(t_map));
	node->pos.y = a/width;
	node->pos.x = a - node->pos.y * width;
	while (b < 7){
		node->objects[b] = rand()%3;
		b++;
	}
	return (node);
}

t_map	**create_map(t_server *server)
{
	t_map	**map;
	t_map	*node;
	int	i = server->width * server->height;
	int	a = 0;

	map = malloc(sizeof(t_map*) * (i + 1));
	if (map == NULL)
		return (NULL);
	while (a < i){
		node = new_node(a, server->width);
		if (node == NULL)
			return (NULL);
		map[a++] = node;
	}
	map[a] = NULL;
	return (map);
}
