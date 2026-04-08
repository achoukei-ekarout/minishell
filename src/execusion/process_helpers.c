/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 08:32:24 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/08 11:17:11 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_left_child(t_ast *node, int fd[2], t_vars *vars, t_garbage garbage)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute_ast(node->left, vars, garbage.temp_gc, garbage.perm_gc);
	exit(0);
}

void	run_right_child(t_ast *node, int fd[2], t_vars *vars, t_garbage garbage)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute_ast(node->right, vars, garbage.temp_gc, garbage.perm_gc);
	exit(0);
}

void	signal_exit(t_vars *vars, int status)
{
	vars->exit_code = 128 + WTERMSIG(status);
	if (WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
	else if (WTERMSIG(status) == SIGQUIT)
		write(2, "Quit (core dumped)\n", 20);
}

void	child_process(t_ast *node, t_vars *vars, t_gc **head_gc)
{
	char	**envp;
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!apply_redirections(node->redir, vars))
		exit(1);
	envp = env_to_array(vars->env, head_gc);
	if (ft_strchr(node->argv[0], '/'))
		return (handle_dir(node->argv, envp));
	else
	{
		path = get_path_name(node->argv[0], get_all_paths(envp, head_gc));
		if (!path)
		{
			ft_putstr_fd(node->argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
	execve(path, node->argv, envp);
	perror("exec");
	exit(1);
}

void	pipe_exit(t_vars *vars, int status2)
{
	if (WIFEXITED(status2))
		vars->exit_code = status2 >> 8;
	else if (WIFSIGNALED(status2))
	{
		vars->exit_code = 128 + WTERMSIG(status2);
		if (WTERMSIG(status2) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status2) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
	}
	if (!isatty(STDIN_FILENO))
		exit(vars->exit_code);
}
