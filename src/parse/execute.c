/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 23:34:32 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/13 17:31:22 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	execute_program(char **arr, char **envp)
// {
// 	int	pid;

// 	if (ft_strncmp(arr[0], "ls", 2) == 0)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			execve("/usr/bin/ls", arr, envp);
// 			exit(1);
// 		}
// 		waitpid(pid, NULL, 0);
// 	}
// }

// void	execute_ast(t_ast *node)
// {
// 	if (!node)
// 		return ;
// 	if (node->type == NODE_PIPE)
// 		execute_pipe(node);
// 	else if (node->type == NODE_COMMAND)
// 		execute_command(node);
// }

// void	execute_pipe(t_ast *node)
// {
// 	int		fd[2];
// 	pid_t	pid1;
// 	pid_t	pid2;

// 	pipe(fd);
// 	pid1 = fork();
// 	if (pid1 == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		execute_ast(node->left);
// 		exit(0);
// 	}
// 	pid2 = fork();
// 	if (pid2 == 0)
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[1]);
// 		execute_ast(node->right);
// 		exit(0);
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// }

// void	execute_command(t_ast *node)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		apply_redirections(node->redir);
// 		execvp(node->argv[0], node->argv);
// 		perror("exec");
// 		exit(1);
// 	}
// 	waitpid(pid, NULL, 0);
// }
