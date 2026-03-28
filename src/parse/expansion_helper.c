/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:56:34 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/27 17:25:10 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *value, int *i, t_vars vars)
{
	int		start;
	char	*key;
	char	*result;

	start = *i;
	if (value[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(vars.exit_code));
	}
	while ((ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	if (*i == start)
		return ("$");
	key = ft_substr(value, start, *i - start);
	result = get_env_value(vars.env, key);
	free(key);
	return (result);
}

void	handle_single_quotes(t_expand *expand_data, int *i, int *j)
{
	(*i)++;
	while (expand_data->old_value[*i] != '\'' && expand_data->old_value[*i])
	{
		expand_data->new_value[*j] = expand_data->old_value[*i];
		(*i)++;
		(*j)++;
	}
	if (expand_data->old_value[*i] == '\'')
		(*i)++;
}

void	handle_dollar(t_expand *expand_data, int *i, int *j)
{
	char	*expanded;
	int		k;

	(*i)++;
	expanded = get_value(expand_data->old_value, i, expand_data->vars);
	if (expanded)
	{
		k = -1;
		while (expanded[++k])
		{
			expand_data->new_value[*j] = expanded[k];
			(*j)++;
		}
		free(expanded);
	}
}

void	handle_double_quotes(t_expand *expand_data, int *i, int *j)
{
	(*i)++;
	while (expand_data->old_value[*i] != '\"' && expand_data->old_value[*i])
	{
		if (expand_data->old_value[*i] == '$')
			handle_dollar(expand_data, i, j);
		else
		{
			expand_data->new_value[*j] = expand_data->old_value[*i];
			(*i)++;
			(*j)++;
		}
	}
	if (expand_data->old_value[*i] == '\"')
		(*i)++;
}
