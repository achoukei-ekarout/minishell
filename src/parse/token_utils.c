/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 00:21:23 by achoukei          #+#    #+#             */
/*   Updated: 2026/04/13 12:49:15 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_token_type type, char *value, t_gc **head_gc)
{
	t_token	*node;
	char	*trimmed;

	if (!value)
		return (NULL);
	trimmed = ft_strtrim(value, " \n\t\v\f\r");
	node = allocate(head_gc, sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup_allocate(trimmed, head_gc);
	node->next = NULL;
	free(trimmed);
	return (node);
}

void	add_token(t_token **head, t_token *node)
{
	t_token	*current;

	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = node;
}

void	replace_token(t_token **head, t_token **prev_node, t_token *new_node)
{
	t_token	*next;

	if (!head && !prev_node)
		return ;
	if (!*prev_node)
	{
		*head = new_node;
		return ;
	}
	next = (*prev_node)->next;
	(*prev_node)->next = new_node;
	while (new_node->next)
		new_node = new_node->next;
	new_node->next = next->next;
}

void	remove_token(t_token **head, t_token **prev, t_token *node)
{
	if (!head && !prev)
		return ;
	if (!*prev)
	{
		*head = node->next;
		return ;
	}
	(*prev)->next = node->next;
}
