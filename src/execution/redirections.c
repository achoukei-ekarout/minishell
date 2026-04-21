/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 08:35:11 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/11 20:27:38 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_redirections(t_redir *redir, t_vars *vars)
{
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_REDIR_APPEND)
		{
			if (!handle_redir_out(redir, vars))
				return (0);
		}
		else if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC
			|| redir->type == TOKEN_HEREDOC_NOEXP)
		{
			if (!handle_redir_in(redir, vars))
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}

int	handle_redir_out(t_redir *redir, t_vars *vars)
{
	int	fd;

	if (redir->type == TOKEN_REDIR_OUT)
		fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd(vars->executer_name, 2);
		ft_putstr_fd(": ", 2);
		perror(redir->file);
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	handle_redir_in(t_redir *redir, t_vars *vars)
{
	int	fd;

	if (redir->type == TOKEN_REDIR_IN)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd(vars->executer_name, 2);
			ft_putstr_fd(": ", 2);
			perror(redir->file);
			return (0);
		}
	}
	else
		fd = redir->fd;
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	*open_redirections(t_redir *redir, t_vars *vars, t_gc **head_gc)
{
	int	*saved_stds;

	if (!redir)
	{
		vars->exit_code = 0;
		return (NULL);
	}
	saved_stds = (int *)allocate(head_gc, sizeof(int) * 2);
	saved_stds[0] = dup(STDIN_FILENO);
	saved_stds[1] = dup(STDOUT_FILENO);
	if (!apply_redirections(redir, vars))
		vars->exit_code = 1;
	else
		vars->exit_code = 0;
	if (g_signal == SIGINT)
		vars->exit_code = 130;
	return (saved_stds);
}

void	close_redirections(int *saved_stds)
{
	if (!saved_stds)
		return ;
	dup2(saved_stds[0], STDIN_FILENO);
	dup2(saved_stds[1], STDOUT_FILENO);
	close(saved_stds[0]);
	close(saved_stds[1]);
}
