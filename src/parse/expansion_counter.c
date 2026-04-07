/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_counter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:57:58 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/07 15:57:47 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_value_len(char *value, int *i, t_vars vars, t_gc **head_gc)
{
	if (ft_strcmp(value, "HOME"))
		return (ft_strlen(get_env_value(vars.env, "HOME")));
	return (ft_strlen(get_value(value, i, vars, head_gc)));
}

void	handle_single_quotes_len(char *value, int *i, int *len)
{
	(*i)++;
	while (value[*i] != '\'' && value[*i])
	{
		(*i)++;
		(*len)++;
	}
	if (value[*i] == '\'')
		i++;
}

void	handle_double_quote_len(char *value, int *i, int *len, t_vars vars, t_gc **head_gc)
{
	(*i)++;
	while (value[*i] != '\"' && value[*i])
	{
		if (value[*i] == '$')
		{
			(*i)++;
			*len += get_value_len(value, i, vars, head_gc);
		}
		else
		{
			(*i)++;
			(*len)++;
		}
	}
	if (value[*i] == '\"')
		(*i)++;
}

int	get_expansion_len(char *value, int *i, t_vars vars, t_gc **head_gc)
{
	if (value[*i] == '$')
		return (get_value_len(value, i, vars, head_gc));
	else if (value[*i] == '~')
		return (get_value_len("HOME", i, vars, head_gc));
	return (0);
}

int	get_new_size(char *value, t_vars vars, t_gc **head_gc)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (value[i])
	{
		if (value[i] == '\'')
			handle_single_quotes_len(value, &i, &len);
		else if (value[i] == '\"')
			handle_double_quote_len(value, &i, &len, vars, head_gc);
		else if (value[i] == '$' || value[i] == '~')
		{
			len += get_expansion_len(value, &i, vars, head_gc);
			i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
