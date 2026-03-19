/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 23:34:32 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/19 22:37:07 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_path_name(char *func_name, char **paths)
{
	int i;
	char *full_path;
	char *add_slash;

	i = 0;
	while (paths[i])
	{
		add_slash = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(add_slash, func_name);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
		free(add_slash);
		free(full_path);
	}
	return (NULL);
}

char *get_path(char **envp)
{
	int i;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", ft_strlen("PATH")))
			return envp[i];
		i++;
	}
	return (NULL);
}

void	execute_ast(t_ast *node, char **envp)
{
	char *path;
	char **paths;
	char *full_path;
	
	full_path = get_path(envp);
	path = ft_substr(full_path, ft_strlen("PATH="), ft_strlen(full_path));
	// free(full_path);
	paths = ft_split(path, ':');
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
		execute_pipe(node, envp);
	else if (node->type == NODE_COMMAND)
		execute_command(node, envp,paths);
}

void	execute_pipe(t_ast *node, char **envp)
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
		execute_ast(node->left, envp);
		exit(0);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		execute_ast(node->right, envp);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	execute_command(t_ast *node, char **envp, char **paths)
{
	int	pid;
	char *path;

	pid = fork();
	if (pid == 0)
	{
		path = get_path_name(node->argv[0], paths);
		// printf("%s\n", path);
		if (!path)
			return ;
		apply_redirections(node->redir);
		// Find the path for the function execve.
		execve(path, node->argv, envp);
		perror("exec");
		exit(1);
	}
	waitpid(pid, NULL, 0);
}

void	apply_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
		{
			fd = open(redir->file, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == TOKEN_REDIR_OUT)
		{
			fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == TOKEN_REDIR_APPEND)
		{
			fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
}
