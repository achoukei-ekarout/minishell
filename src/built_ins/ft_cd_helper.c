/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:10:59 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/09 06:10:45 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_back_count(char *dir)
{
	int		i;
	int		count;
	int		done;

	i = 2;
	count = 0;
	done = 0;
	while(!done)
	{
		while(dir[i])
		{
			if (dir[i] == '/' || !dir[i])
				break ;
			i++;
		}
		if (!dir[i])
			done = 1 ;
		if (ft_strncmp("..", dir + i, 2))
			done = 1 ;
		count++;
		i++;
	}
	return (count);
}

char	*go_back_path(char *dir, char *last_dir)
{
	char	*path;
	int		count;
	int		last;

	count = check_back_count(dir);
	while (count)
	{
		last = ft_strlen(last_dir) - ft_strlen(ft_strrchr(last_dir, '/'));
		last_dir[last] = 0;
		count--;
	}
	path = ft_strdup(last_dir);
	return(path);
}

char	*ft_go_home(char *dir, t_env *env)
{
	char	*home;
	char	*temp;
	char	*path;
	int		result;

	home = get_env_value(env, "HOME");
	if (ft_isempty(dir))
		path = ft_strdup(home);
	else
	{
		temp = ft_substr(dir, 1, ft_strlen(dir));
		path = ft_strjoin(home, temp);
		free(temp);
	}
	result = chdir(path);
	if (result == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putchar_fd('\n', 2);
		return (NULL);
	}
	return (path);
}

char	*ft_go_back(char *dir, t_env *env)
{
	char	*path;
	char	*pwd;
	int		result;

	pwd = get_env_value(env, "PWD");
	path = go_back_path(dir, pwd);
	result = chdir(path);
	if (result == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putchar_fd('\n', 2);
		return (NULL);
	}
	return(path);
}

char	*ft_go_dir(char *dir, t_env *env)
{
	char	*pwd;
	char	*new_dir;
	char	*path;
	int		result;

	pwd = get_env_value(env, "PWD");
	if (ft_strncmp(dir, "/", 1))
	{
		new_dir = ft_strjoin("/", dir);
		path = ft_strjoin(pwd, new_dir);
		free(new_dir);
	}
	else
		path = ft_strjoin(pwd, dir);
	result = chdir(dir);
	if (result == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putchar_fd('\n', 2);
		return (NULL);
	}
	return (path);
}
