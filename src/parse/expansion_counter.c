/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_counter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:57:58 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/08 13:15:36 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_value_len(char *value, int *i, t_vars vars)
{
	char	*new_value;
	int		len;

	if (value[*i] == '$')
	{
		(*i)++;
		new_value = get_value(value, i, vars);
		len = ft_strlen(new_value);
		free(new_value);
		return (len);
	}
	(*i)++;
	new_value = get_value("HOME", i, vars);
	len = ft_strlen(new_value);
	free(new_value);
	return (len);
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

void	handle_double_quote_len(char *value, int *i, int *len, t_vars vars)
{
	(*i)++;
	while (value[*i] != '\"' && value[*i])
	{
		if (value[*i] == '$')
			*len += get_value_len(value, i, vars);
		else
		{
			(*i)++;
			(*len)++;
		}
	}
	if (value[*i] == '\"')
		(*i)++;
}

int	get_new_size(char *value, t_vars vars)
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
			handle_double_quote_len(value, &i, &len, vars);
		else if (value[i] == '$' || value[i] == '~')
			len += get_value_len(value, &i, vars);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
