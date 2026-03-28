/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 00:21:23 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/27 21:35:23 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_token_type type, char *value, t_gc **head_gc)
{
	t_token	*node;

	if (!value)
		return (NULL);
	node = allocate(head_gc, sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup_allocate(value, head_gc);
	node->next = NULL;
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

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens->next)
	{
		tmp = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	get_quote_index(char *line, int *i)
{
	int	start;

	start = (*i)++;
	while (line[*i] && line[*i] != line[start])
		(*i)++;
	while (line[*i] && line[*i] != ' ')
		(*i)++;
	return (start);
}
