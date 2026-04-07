/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:56:34 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/07 10:10:21 by ekarout          ###   ########.fr       */
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
	if (ft_isdigit(value[*i]))
	{
		(*i)++;
		return (NULL);
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

void	handle_character(t_expand *expand_data, int *i, int *j)
{
	if ((expand_data->old_value)[*i] == '$')
		handle_dollar(expand_data, i, j);
	else if ((expand_data->old_value)[*i] == '~')
		handle_tilde(expand_data, i, j);
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
	}
}

void	handle_tilde(t_expand *expand_data, int *i, int *j)
{
	char	*expanded;
	int		k;

	(*i)++;
	expanded = get_env_value(expand_data->vars.env, "HOME");
	if (expanded)
	{
		k = -1;
		while (expanded[++k])
		{
			expand_data->new_value[*j] = expanded[k];
			(*j)++;
		}
	}
}

void	handle_dollar_token(t_expand *expand_data, int *i, int *j)
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
	}
}
