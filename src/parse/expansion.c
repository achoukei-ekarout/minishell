/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:39:34 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/31 06:20:25 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand	*init_expand_data(char *value, t_vars vars, int len, t_gc **head_gc)
{
	t_expand	*expand_data;

	expand_data = (t_expand *)allocate(head_gc, sizeof(t_expand));
	expand_data->old_value = value;
	expand_data->new_value = (char *)allocate(head_gc, sizeof(char) * len);
	expand_data->vars = vars;
	return (expand_data);
}

char	*expand_value(char *value, t_vars vars, t_gc **head_gc)
{
	t_expand	*expand_data;
	int			i;
	int			j;

	i = get_new_size(value, vars) + 1;
	expand_data = init_expand_data(value, vars, i, head_gc);
	i = 0;
	j = 0;
	while (expand_data->old_value[i])
	{
		if (value[i] == '\'')
			handle_single_quotes(expand_data, &i, &j);
		else if (value[i] == '\"')
			handle_double_quotes(expand_data, &i, &j);
		else if (value[i] == '$')
			handle_dollar(expand_data, &i, &j);
		else
		{
			expand_data->new_value[j] = value[i];
			i++;
			j++;
		}
	}
	expand_data->new_value[j] = 0;
	return (expand_data->new_value);
}

int	get_start(char *s)
{
	int	i;

	i = 0;
	while(s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (0);
}

t_token	*expanded_token(char *value, t_vars vars, t_gc **head_gc)
{
	char	**split;
	char	*new_value;
	t_token	*start_node;
	t_token	*next_node;
	int		i;

	i = get_start(value);
	new_value = NULL;
	if (i)
	{
		new_value = ft_substr_allocate(expand_value(value, vars, head_gc),
					0, i, head_gc);
	}
	i++;
	split = ft_split_allocate(get_value(value, &i, vars), ' ',  head_gc);
	if (!split[1])
		return (NULL);
	if (new_value)
		start_node = create_token(TOKEN_WORD, ft_strjoin_allocate(new_value, split[0], head_gc), head_gc);
	else
		start_node = create_token(TOKEN_WORD, split[0], head_gc);
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

int	check_for_new_token(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\'')
		{
			i++;
			while(value[i] && value[i] != '\'')
				i++;
		}
		if (value[i] == '\"')
		{
			i++;
			while(value[i] && value[i] != '\"')
				i++;
		}
		if(value[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

t_token	*expand(t_token **token, t_vars vars, t_gc **head_gc)
{
	char	*value;
	char	*new_value;
	t_token	*tokens;
	int		new_token;

	value = (*token)->value;
	new_token = check_for_new_token(value);
	if (new_token)
		tokens = expanded_token(value, vars, head_gc);
	if (!new_token || !tokens)
	{
		new_value = expand_value(value, vars, head_gc);
		(*token)->value = new_value;
		return (NULL);
	}
	return (tokens);
}

void	param_expand(t_token **tokens, t_vars vars, t_gc **head_gc)
{
	t_token	*curr;
	t_token *prev;
	t_token	*new_token;

	curr = *tokens;
	prev = NULL;
	while (curr)
	{
		new_token = expand(&curr, vars, head_gc);
		if (new_token)
			replace_token(tokens, &prev, new_token);
		prev = curr;
		curr = curr->next;
	}
}
