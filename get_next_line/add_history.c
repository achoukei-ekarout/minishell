/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 10:31:13 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/06 10:58:53 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_history	*create_history_node(char *line, t_gc **perm_gc)
{
	t_history	*new;

	if (!line)
		return (NULL);
	new = (t_history *)allocate(perm_gc, sizeof(t_history));
	if (!new)
		return (NULL);
	new->line = ft_strdup_allocate(line, perm_gc);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_add_history(t_history **history, char *line, t_gc **perm_gc)
{
	t_history	*new;
	t_history	*current;

	if (!line || !*line)
		return ;
	new = create_history_node(line, perm_gc);
	if (!*history)
	{
		*history = new;
		return ;
	}
	current = *history;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
}
