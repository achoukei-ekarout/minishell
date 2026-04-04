/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 23:34:32 by achoukei          #+#    #+#             */
/*   Updated: 2026/04/04 22:27:49 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_ast(t_ast *node, t_vars *vars, t_gc **head_gc, t_gc **perm_gc)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
		execute_pipe(node, vars, head_gc, perm_gc);
	else if (node->type == NODE_COMMAND)
		execute_command(node, vars, head_gc, perm_gc);
}

void	execute_pipe(t_ast *node, t_vars *vars, t_gc **head_gc, t_gc **perm_gc)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int status1;
	int status2;
	
	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execute_ast(node->left, vars, head_gc, perm_gc);
		exit(0);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		execute_ast(node->right, vars, head_gc, perm_gc);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
    vars->exit_code = WEXITSTATUS(status2);
	else if (WIFSIGNALED(status2))
	{
		vars->exit_code = 128 + WTERMSIG(status2);

		if (WTERMSIG(status2) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status2) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
	}
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
	// if (access(node->argv[0], X_OK) == 0)
	// 	path = node->argv[0];
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

void	execute_command(t_ast *node, t_vars *vars, t_gc **gc, t_gc **perm_gc)
{
	int		pid;
	int		saved_stds[2];
	int		status;

	if (is_built_ins(node->argv[0]))
	{
		saved_stds[0] = dup(STDIN_FILENO);
		saved_stds[1] = dup(STDOUT_FILENO);
		if (!apply_redirections(node->redir, vars))
		{
			vars->exit_code = 1;
			dup2(saved_stds[0], STDIN_FILENO);
			dup2(saved_stds[1], STDOUT_FILENO);
			close(saved_stds[0]);
			close(saved_stds[1]);
			return ;
		}
		vars->exit_code = call_built_ins(node->argv, vars, gc, perm_gc);
		if (g_signal == SIGINT)
			vars->exit_code = 130;
		dup2(saved_stds[0], STDIN_FILENO);
		dup2(saved_stds[1], STDOUT_FILENO);
		close(saved_stds[0]);
		close(saved_stds[1]);
		return ;
	}
	pid = fork();
	if (pid == 0)
		child_process(node, vars, gc);
	waitpid(pid, &status, 0);
	// if (WIFEXITED(status))
	// 	vars->exit_code = WEXITSTATUS(status);
	if (!isatty(STDIN_FILENO))
	{
		vars->exit_code = status >> 8;
		exit(vars->exit_code);
	}
	else if (WIFSIGNALED(status))
	{
		vars->exit_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
	}
}

// void	apply_redirections(t_redir *redir)
// {
// 	int	fd;

// 	while (redir)
// 	{
// 		if (redir->type == TOKEN_REDIR_OUT)
// 		{
// 			fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		else if (redir->type == TOKEN_REDIR_APPEND)
// 		{
// 			fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		else if (redir->type == TOKEN_REDIR_IN)
// 		{
// 			fd = open(redir->file, O_RDONLY);
// 			dup2(fd, STDIN_FILENO);
// 			close(fd);
// 		}
// 		else if (redir->type == TOKEN_HEREDOC)
// 		{
// 			dup2(redir->fd, STDIN_FILENO);
// 			close(redir->fd);
// 		}
// 		redir = redir->next;
// 	}
// }

int	apply_redirections(t_redir *redir, t_vars *vars)
{
	int	fd;

	while (redir)
	{
		if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_REDIR_APPEND)
		{
			if (redir->type == TOKEN_REDIR_OUT)
				fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
			{
				perror(redir->file);
				return (0);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC
			|| redir->type == TOKEN_HEREDOC_NOEXP)
		{
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
		}
		redir = redir->next;
	}
	return (1);
}

void	handle_dir(char **argv, char **envp)
{
	struct stat	st;
	char	*dir;

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
