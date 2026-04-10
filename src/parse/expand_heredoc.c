/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:59:11 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/11 00:36:20 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes_heredoc_len(char *value, int *i, int *len)
{
	int	quote;

	quote = *i;
	(*i)++;
	while (value[*i] && value[*i] != value[quote])
	{
		(*len)++;
		(*i)++;
	}
	if (value[*i] == value[quote])
		(*i)++;
}

int	expand_heredoc_len(char *value)
{
	int	len;
	int	i;
	
	i = 0;
	len = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '\"')
			handle_quotes_heredoc_len(value, &i, &len);
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

void	handle_quotes_heredoc(char *value, char *new_value, int *i, int *j)
{
	int	quote;

	quote = *i;
	(*i)++;
	while (value[*i] && value[*i] != value[quote])
	{
		new_value[*j] = value[*i];
		(*i)++;
		(*j)++;
	}
	if (value[*i] == value[quote])
		(*i)++;
}

char	*expand_heredoc(char *value, t_gc **head_gc)
{
	char	*new_value;
	int		i;
	int		j;

	j = expand_heredoc_len(value);
	new_value = (char *)allocate(head_gc, (j + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '\"')
			handle_quotes_heredoc(value, new_value, &i, &j);
		else
		{
			new_value[j] = value[i];
			i++;
			j++;
		}
	}
	new_value[j] = 0;
	return (new_value);
}
