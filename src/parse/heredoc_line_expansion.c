/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_line_expansion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:10:07 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/13 19:24:50 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_new_line_size(char *line, t_vars vars)
{
	int		len;
	int		i;
	char	*new_value;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			new_value = get_value(line, &i, vars);
			len += ft_strlen(new_value);
			free(new_value);
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*heredoc_line_expand(char *line, t_vars vars, t_gc **head_gc)
{
	t_expand	*expand_data;
	int			i;
	int			j;

	j = get_new_line_size(line, vars) + 1;
	expand_data = init_expand_data(line, vars, j, head_gc);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			handle_dollar(expand_data, &i, &j);
			continue ;
		}
		expand_data->new_value[j] = line[i];
		j++;
		i++;
	}
	expand_data->new_value[j] = 0;
	return (expand_data->new_value);
}
