/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:10:59 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/07 09:59:43 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_go_home(char *dir, t_env **env, t_vars *vars)
{
	char	*home;
	int		result;

	home = get_env_value(env, "HOME");
	result = chdir(home);
	if (result == -1)
		return (cd_dir_error(dir, *vars));
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

int	ft_go_dir(char *dir, t_vars *vars)
{
	int		result;

	result = chdir(dir);
	if (result == -1)
		return (cd_dir_error(dir, *vars));
	return (result);
}
