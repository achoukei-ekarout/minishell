/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 23:34:32 by achoukei          #+#    #+#             */
/*   Updated: 2026/04/08 19:10:56 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_ast(t_ast *node, t_vars *vars, t_gc **head_gc, t_gc **perm_gc)
{
	t_garbage	garbage;

	garbage.temp_gc = head_gc;
	garbage.perm_gc = perm_gc;
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
		execute_pipe(node, vars, garbage);
	else if (node->type == NODE_COMMAND)
		execute_command(node, vars, garbage);
}

void	execute_pipe(t_ast *node, t_vars *vars, t_garbage garbage)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int	status1;
	int	status2;

	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
		run_left_child(node, fd, vars, garbage);
	pid2 = fork();
	if (pid2 == 0)
		run_right_child(node, fd, vars, garbage);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	pipe_exit(vars, status2);
}

void	handle_built_ins(t_ast *node, t_vars *vars, t_garbage garbage)
{
	int	*saved_stds;

	saved_stds = open_redirections(node->redir, vars, garbage.temp_gc);
	if (!vars->exit_code)
		vars->exit_code = call_built_ins(node->argv, vars, garbage);
	if (g_signal == SIGINT)
		vars->exit_code = 130;
	close_redirections(saved_stds);
	if (!isatty(STDIN_FILENO))
		exit(vars->exit_code);
}

void	execute_command(t_ast *node, t_vars *vars, t_garbage garbage)
{
	int		pid;
	int		*saved_stds;
	int		status;

	if (!node->argv)
	{
		saved_stds = open_redirections(node->redir, vars, garbage.temp_gc);
		close_redirections(saved_stds);
		if (!isatty(STDIN_FILENO))
			exit(vars->exit_code);
		return ;
	}
	if (is_built_ins(node->argv[0]))
		return (handle_built_ins(node, vars, garbage));
	pid = fork();
	if (pid == 0)
		child_process(node, vars, garbage.temp_gc);
	waitpid(pid, &status, 0);
	vars->exit_code = status >> 8;
	if (!isatty(STDIN_FILENO))
		exit(vars->exit_code);
	else if (WIFSIGNALED(status))
		signal_exit(vars, status);
}

void	handle_dir(char **argv, char **envp)
{
	struct stat	st;
	char		*dir;

	dir = argv[0];
	if (stat(dir, &st) == -1)
	{
		perror(dir);
		exit(127);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	if (access(dir, X_OK) != 0)
	{
		perror(dir);
		exit(126);
	}
	execve(dir, argv, envp);
	perror("exec");
	exit(1);
}
