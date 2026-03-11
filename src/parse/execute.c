/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 23:34:32 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/11 04:14:49 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_program(char **arr, char **envp)
{
	int	pid;

	if (ft_strncmp(arr[0], "ls", 2) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			execve("/usr/bin/ls", arr, envp);
			exit(1);
		}
		waitpid(pid, NULL, 0);
	}
}
