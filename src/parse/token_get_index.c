/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_get_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 23:31:36 by achoukei          #+#    #+#             */
/*   Updated: 2026/04/21 15:44:55 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quote_index(char *line, int *i, t_vars *vars)
{
	int	start;
	int	quote;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i]))
	{
		if (is_quote(line[*i]))
			quote = *i;
		(*i)++;
		while (line[*i] && line[*i] != line[quote])
			(*i)++;
		if (!line[*i])
			return (quotes_error(*vars));
		if (line[*i])
			(*i)++;
		if (is_quote(line[*i]))
		{
			quote = *i;
			continue ;
		}
		while (line[*i] && !ft_isspace(line[*i]) && !is_quote(line[*i]))
			(*i)++;
	}
	return (start);
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}
