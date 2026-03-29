/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 20:47:34 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/28 20:52:41 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gc	*create_gc_node(void *ptr)
{
	t_gc	*node;

	node = malloc(sizeof(t_gc));
	node->value = ptr;
	node->next = NULL;
	return (node);
}

void	*allocate(t_gc **head, size_t size)
{
	t_gc	*current;
	void	*ptr;
	t_gc	*node;

	if (!*head)
	{
		ptr = malloc(size);
		node = create_gc_node(ptr);
		*head = node;
		return (ptr);
	}
	current = *head;
	ptr = malloc(size);
	node = create_gc_node(ptr);
	while (current->next)
		current = current->next;
	current->next = node;
	return (ptr);
}

void	free_garbage(t_gc **head)
{
	t_gc	*current;
	t_gc	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		if(current->value)
			free(current->value);
		free(current);
		current = next;
	}
}
