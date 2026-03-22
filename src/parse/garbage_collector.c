/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 20:47:34 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/22 21:49:21 by achoukei         ###   ########.fr       */
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

char	*allocate(t_gc **head, size_t size)
{
	t_gc	*current;
	void	*ptr;
	t_gc	*node;

	current = *head;
	ptr = malloc(size);
	node = create_gc_node(ptr);
	while (current->next)
		current = current->next;
	current->next = node;
	return (ptr);
}

void free_garbage(t_gc **head)
{
    t_gc *current;
    t_gc *next;

    while (current)
    {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}