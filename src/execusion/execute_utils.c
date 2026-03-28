/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:21:48 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/27 17:52:46 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_all_paths(char **envp, t_gc **head_gc)
{
	char	*path;
	char	*full_path;
	char	**paths;

	full_path = get_path(envp);
	path = ft_substr_allocate(full_path, ft_strlen("PATH="),
			ft_strlen(full_path), head_gc);
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

int	is_built_ins(char *str)
{
	char	**built_ins;
	int		i;

	built_ins = malloc(sizeof(char *) * 8);
	built_ins[0] = ft_strdup("echo");
	built_ins[1] = ft_strdup("cd");
	built_ins[2] = ft_strdup("pwd");
	built_ins[3] = ft_strdup("export");
	built_ins[4] = ft_strdup("unset");
	built_ins[5] = ft_strdup("env");
	built_ins[6] = ft_strdup("exit");
	built_ins[7] = NULL;
	i = 0;
	while (built_ins[i])
	{
		if (ft_strcmp(str, built_ins[i]) == 0)
		{
			built_ins = free_arr(&built_ins);
			return (1);
		}
		i++;
	}
	built_ins = free_arr(&built_ins);
	return (0);
}

int	call_built_ins(char *str, char **input, t_vars vars)
{
	int	result;

	result = -1;
	if (ft_strcmp(str, "echo") == 0)
		result = ft_echo(input);
	else if (ft_strcmp(str, "cd") == 0)
		result = ft_cd(input, vars.env);
	else if (ft_strcmp(str, "pwd") == 0)
		result = ft_pwd(vars.env);
	else if (ft_strcmp(str, "export") == 0)
		result = ft_export(input, vars.env, vars.exp);
	else if (ft_strcmp(str, "unset") == 0)
		result = ft_unset(input, vars.env, vars.exp);
	else if (ft_strcmp(str, "env") == 0)
		result = ft_env(vars.env);
	else if (ft_strcmp(str, "exit") == 0)
		ft_exit(input);
	return (result);
}
