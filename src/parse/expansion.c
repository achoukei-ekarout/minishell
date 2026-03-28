/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:39:34 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/27 19:01:00 by ekarout          ###   ########.fr       */
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

void	expand(t_token **token, t_vars vars, t_gc **head_gc)
{
	char	*value;
	char	*new_value;

	value = (*token)->value;
	new_value = expand_value(value, vars, head_gc);
	(*token)->value = new_value;
}

void	param_expand(t_token **tokens, t_vars vars, t_gc **head_gc)
{
	t_token	*curr;

	curr = *tokens;
	while (curr)
	{
		expand(&curr, vars, head_gc);
		curr = curr->next;
	}
}
