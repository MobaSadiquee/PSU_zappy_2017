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

t_cmd *stack_pop(t_stack *stack)
{
	t_stacknode *old;
	t_cmd *cmd;

	if (stack->top == NULL)
		return (0);
	old = stack->top;
	cmd = old->cmd;
	stack->top = old->next;
	if (stack->top != NULL)
		gettimeofday(&stack->time, NULL);
	if (old->args)
		free(old->args);
	free(old);
	old = NULL;
	stack->count--;
	return cmd;
}

void stack_clean(t_stack *stack)
{
	while (!is_stack_empty(stack))
		stack_pop(stack);
}

void stack_destroy(t_stack *stack)
{
	stack_clean(stack);
	free(stack);
}

int stack_push(t_stack *stack, t_cmd *cmd, char *args)
{
	t_stacknode *tmp = stack->top;
	t_stacknode *new_node = alloc_stacknode(cmd);

	if (new_node == NULL || stack->count >= 10)
		return (0);
	if (args)
		new_node->args = strdup(args);
	if (tmp == NULL) {
		gettimeofday(&stack->time, NULL);
		stack->top = new_node;
	}
	else {
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	stack->count++;
	return (1);
}
