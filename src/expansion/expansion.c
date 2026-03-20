/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:39:34 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/20 18:59:13 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand	*init_expand_data(char *value, t_env **env)
{
	t_expand	*expand_data;

	expand_data = (t_expand *)malloc(sizeof(t_expand));
	expand_data->old_value = value;
	expand_data->new_value = (char *)malloc(sizeof(char) * (i + 1));
	expand_data->env = env;
	return (expand_data);
}

char	*expand_value(char *value, t_env **env)
{
	t_expand	*expand_data;
	int			i;
	int			j;

	i = get_new_size(value, env);
	expand_data = init_expand_data(value, env);
	expand_data->new_value[i] = 0;
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
	return (expand_data->new_value);
}

void	expand(t_token **token, t_env **env)
{
	char	*value;
	char	*new_value;

	expand_value(value, env);
	free((*token)->value);
	(*token)->value = new_value;
}

void	param_expand(t_token **tokens, t_env **env)
{
	t_token	*curr;

	curr = *tokens;
	while (curr)
	{
		expand(&curr, env);
		curr = curr->next;
	}
}
