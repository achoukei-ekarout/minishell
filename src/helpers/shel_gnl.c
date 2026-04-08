/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_gnl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 12:45:36 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/07 08:01:52 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_gnl_expand(char *delimeter, int fd_out,
		t_vars *vars, t_gc **head_gc)
{
	char	*line;
	char	*expand;

	ft_putstr_fd("> ", 0);
	line = get_next_line(0);
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
	expand = expand_value(line, *vars, head_gc);
	write(fd_out, expand, ft_strlen(expand));
	vars->line_counter++;
	write(fd_out, "\n", 1);
	free(line);
	return (1);
}

int	heredoc_gnl(char *delimeter, int fd_out, t_vars *vars)
{
	char	*line;

	ft_putstr_fd("> ", 0);
	line = get_next_line(0);
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

void	run_shell_gnl(t_vars *vars, t_gc **perm_gc)
{
	char		*input;
	t_gc		*gc;

	while (1)
	{
		setup_signals_prompt();
		g_signal = 0;
		gc = NULL;
		ft_putstr_fd("minishell$ ", 0);
		input = get_next_line(0);
		if (g_signal == SIGINT)
			vars->exit_code = 130;
		vars->line_counter ++;
		if (!input)
		{
			ft_putchar_fd('\n', 0);
			input = "exit";
		}
		if (!*input)
			continue ;
		read_input(input, vars, &gc, perm_gc);
		free_garbage(&gc);
		free(input);
	}
}
