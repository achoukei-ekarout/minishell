/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 05:19:03 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/09 21:33:53 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_readline_expand(char *delimeter, int fd_out,
		t_vars *vars, t_gc **head_gc)
{
	char	*line;
	char	*expand;

	line = readline("> ");
	if (!line)
	{
		heredoc_error(*vars);
		return (0);
	}
	if (ft_strcmp(line, delimeter) == 0)
	{
		free(line);
		return (0);
	}
	if (*line)
		add_history(line);
	expand = expand_value(line, *vars, head_gc);
	write(fd_out, expand, ft_strlen(expand));
	vars->line_counter++;
	write(fd_out, "\n", 1);
	free(line);
	return (1);
}

int	heredoc_readline(char *delimeter, int fd_out, t_vars *vars)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		heredoc_error(*vars);
		return (0);
	}
	if (ft_strcmp(line, delimeter) == 0)
	{
		free(line);
		return (0);
	}
	write(fd_out, line, ft_strlen(line));
	vars->line_counter++;
	write(fd_out, "\n", 1);
	free(line);
	return (1);
}
