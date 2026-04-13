/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 05:19:03 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/13 15:04:57 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child_process(int fd[2], struct s_heredoc heredoc_vars,
	t_vars *vars, t_gc **head_gc)
{
	char			*delimeter;
	t_token_type	type;

	delimeter = heredoc_vars.delimeter;
	type = heredoc_vars.type;
	close(fd[0]);
	setup_signals_heredoc();
	if (type == TOKEN_HEREDOC)
		while (heredoc_readline_expand(delimeter, fd[1], vars, head_gc))
			continue ;
	else
		while (heredoc_readline(delimeter, fd[1], vars))
			continue ;
	close(fd[1]);
	exit(0);
}

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
			if (redir->fd != -1)
				close(redir->fd);
		redir = redir->next;
	}
}
