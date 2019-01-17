/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** commands stack
*/

#include <stdlib.h>
#include <sys/time.h>
#include <string.h> // TEMPORARY
#include "server.h"

int is_stack_empty(t_stack *stack)
{
	return (stack->top == NULL ? 1 : 0);
}

int get_stack_size(t_stack *stack)
{
	return (stack->count);
}

t_cmd *stack_top(t_stack *stack)
{
	return (stack->top->cmd);
}

t_stacknode *alloc_stacknode(t_cmd *cmd)
{
	t_stacknode *new_node = malloc(sizeof(t_stacknode));

	if (new_node == NULL)
		return (NULL);
	new_node->cmd = cmd;
	new_node->args = NULL;
	new_node->next = NULL;
	return (new_node);
}
