/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_get_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 23:31:36 by achoukei          #+#    #+#             */
/*   Updated: 2026/04/04 18:13:47 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quote_index(char *line, int *i, t_vars *vars)
{
	int	start;

	start = (*i)++;
	while (line[*i] && line[*i] != line[start])
	{
		(*i)++;
		if (!line[*i])
		{
			quotes_error(*vars);
			return (-1);
		}
	}
	while (line[*i] && line[*i] != ' ')
		(*i)++;
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
