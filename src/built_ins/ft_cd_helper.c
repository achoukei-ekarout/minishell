/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:10:59 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/11 01:09:33 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_go_home(char *dir, t_env **env, t_vars vars)
{
	char	*home;
	int		result;
	char	*temp;

	home = get_env_value(env, "HOME");
	if (!home)
	{
		temp = ft_strjoin(vars.executer_name, ": cd: HOME not set\n");
		ft_putstr_fd(temp , 2);
		free(temp);
		return (-1);
	}
	result = chdir(home);
	if (result == -1)
		return (cd_dir_error(dir, vars));
	return (result);
}

int	ft_go_back(t_env **env, t_vars vars)
{
	char	*temp;

	if (!get_env_value(env, "OLDPWD"))
	{
		temp = ft_strjoin(vars.executer_name, ": cd: OLDPWD not set\n");
		ft_putstr_fd(temp, 2);
		free(temp);
		return (-1);
	}
	else
		return (chdir(get_env_value(env, "OLDPWD")));
}

int	ft_go_dir(char *dir, t_vars *vars)
{
	int		result;

	result = chdir(dir);
	if (result == -1)
		return (cd_dir_error(dir, *vars));
	return (result);
}
