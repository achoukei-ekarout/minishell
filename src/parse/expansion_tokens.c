/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 17:02:37 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/08 13:13:11 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_start(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (0);
}

t_token	*start_node(char *new_value, char **split, t_gc **head_gc)
{
	t_token	*start_node;
	t_token	*next_node;
	char	*token_value;
	int		i;

	if (new_value)
		token_value = ft_strjoin_allocate(new_value, split[0], head_gc);
	else
		token_value = split[0];
	start_node = create_token(TOKEN_WORD, token_value, head_gc);
	i = 1;
	next_node = start_node;
	while (split[i])
	{
		next_node->next = create_token(TOKEN_WORD, split[i], head_gc);
		next_node = next_node->next;
		i++;
	}
	return (start_node);
}

t_token	*expanded_token(char *value, t_vars vars, t_gc **head_gc)
{
	char	**split;
	char	*new_value;
	char	*expanded;
	int		i;

	i = get_start(value);
	new_value = NULL;
	if (i)
	{
		new_value = ft_substr_allocate(expand_value(value, vars, head_gc),
				0, i, head_gc);
	}
	i++;
	expanded = get_value(value, &i, vars);
	split = ft_split_allocate(expanded, ' ', head_gc);
	free(expanded);
	if (!split)
		return (NULL);
	if (!split[0])
		return (NULL);
	if (!split[1])
		return (NULL);
	return (start_node(new_value, split, head_gc));
}

int	check_for_new_token(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\'')
		{
			i++;
			while (value[i] && value[i] != '\'')
				i++;
		}
		if (value[i] == '\"')
		{
			i++;
			while (value[i] && value[i] != '\"')
				i++;
		}
		if (value[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
