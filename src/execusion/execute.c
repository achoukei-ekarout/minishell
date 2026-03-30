/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 23:34:32 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/31 00:15:51 by achoukei         ###   ########.fr       */
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

	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execute_ast(node->left, vars, head_gc, perm_gc);
		exit(0);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		execute_ast(node->right, vars, head_gc, perm_gc);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	child_process(t_ast *node, t_vars *vars, t_gc **head_gc)
{
	char	**envp;
	char	*path;

	apply_redirections(node->redir);
	envp = env_to_array(vars->env, head_gc);
	if (access(node->argv[0], X_OK) == 0)
		path = node->argv[0];
	else
	{
		path = get_path_name(node->argv[0], get_all_paths(envp, head_gc));
		if (!path)
		{
			printf("%s: command not found\n", node->argv[0]);
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
		apply_redirections(node->redir);
		vars->exit_code = call_built_ins(node->argv, vars, gc, perm_gc);
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
	vars->exit_code = status >> 8;
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

void	apply_redirections(t_redir *redir)
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
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC
		|| redir->type == TOKEN_HEREDOC_NOEXP)
		{
			if (redir->type == TOKEN_REDIR_IN)
				fd = open(redir->file, O_RDONLY);
			else
				fd = redir->fd;
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
}
