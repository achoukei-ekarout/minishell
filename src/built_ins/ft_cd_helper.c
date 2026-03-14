/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:10:59 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/13 22:34:06 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_go_home(char *dir, t_env **env)
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
	free(path);
	if (result == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putchar_fd('\n', 2);
		return ;
	}
}

void	ft_go_back(t_env **env)
{
	if (!get_env_value(env, "OLDPWD"))
		ft_putstr_fd("cd: OLDPWD not set", 2);
	else
		chdir(get_env_value(env, "OLDPWD"));
}

void	ft_go_dir(char *dir)
{
	int		result;

	result = chdir(dir);
	if (result == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putchar_fd('\n', 2);
		return ;
	}
}
