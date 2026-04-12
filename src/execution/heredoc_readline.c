/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 05:19:03 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/12 14:03:09 by ekarout          ###   ########.fr       */
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
	if (*line)
		add_history(line);
	write(fd_out, line, ft_strlen(line));
	vars->line_counter++;
	write(fd_out, "\n", 1);
	free(line);
	return (1);
}

void	close_heredoc_fds(t_ast *node)
{
	t_redir	*redir;

	redir = node->redir;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC || redir->type == TOKEN_HEREDOC_NOEXP)
			if(redir->fd != -1)
				close(redir->fd);
		redir = redir->next;
	}
}
