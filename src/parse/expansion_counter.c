/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_counter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:57:58 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/26 21:13:14 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_value_len(char *value, int *i, t_vars vars)
{
	int		start;
	char	*key;
	char	*result;
	int		len;

	start = *i;
	if (value[*i] == '?')
	{
		(*i)++;
		result = ft_itoa(vars.exit_code);
		len = ft_strlen(result);
		free(result);
		return (len);
	}
	while ((ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (1);
	key = ft_substr(value, start, *i - start);
	result = get_env_value(vars.env, key);
	free(key);
	if (!result)
		return (0);
	return (ft_strlen(result));
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
		{
			(*i)++;
			*len += get_value_len(value, i, vars);
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

int	get_new_size(char *value, t_vars vars)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (value[i])
	{
		if (value[i] == '\'')
			handle_single_quotes_len(value, &i, &len);
		else if (value[i] == '\"')
			handle_double_quote_len(value, &i, &len, vars);
		else if (value[i] == '$')
		{
			i++;
			len += get_value_len(value, &i, vars);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
