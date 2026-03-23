/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:21:48 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/23 19:32:22 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_all_paths(char **envp, t_gc **head_gc)
{
	char	*path;
	char	*full_path;
	char **paths;
	
	full_path = get_path(envp);
	path = ft_substr_allocate(full_path, ft_strlen("PATH="), ft_strlen(full_path), head_gc);
	paths = ft_split_allocate(path, ':', head_gc);
	return (paths);
}

char	*get_path_name(char *func_name, char **paths)
{
	int		i;
	char	*full_path;
	char	*add_slash;

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

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", ft_strlen("PATH")))
			return (envp[i]);
		i++;
	}
	return (NULL);
}
