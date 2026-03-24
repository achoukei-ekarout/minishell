/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:10:59 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/24 12:55:49 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_go_home(char *dir, t_env **env)
{
	char	*home;
	char	*temp;
	char	*path;
	int		result;

	home = get_env_value(env, "HOME");
	if (!dir)
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
		return (cd_dir_error(dir));
	return (result);
}

int	ft_go_back(t_env **env)
{
	if (!get_env_value(env, "OLDPWD"))
	{
		ft_putstr_fd("cd: OLDPWD not set", 2);
		return (-1);
	}
	else
		return (chdir(get_env_value(env, "OLDPWD")));
}

int	ft_go_dir(char *dir)
{
	int		result;

	result = chdir(dir);
	if (result == -1)
		return (cd_dir_error(dir));	
	return (result);
}
