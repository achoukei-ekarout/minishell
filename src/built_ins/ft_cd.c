/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:08:53 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/13 22:32:43 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isempty(char	*arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] != '\f' && arg[i] != ' ' && arg[i] != '\t'
			&& arg[i] != '\n' && arg[i] != '\r' && arg[i] != '\v')
			break ;
		i++;
	}
	if (!arg[i])
		return (1);
	return (0);
}

void	change_env_pwd(char *old_path, t_env **env)
{
	char	*new_path;

	new_path = getcwd(NULL, 0);
	change_env_value(env, "OLDPWD", old_path);
	change_env_value(env, "PWD", new_path);
	free(new_path);
}

void	ft_cd(char *arg, t_env **env)
{
	char	*old_path;

	old_path = getcwd(NULL, 0);
	if (ft_isempty(arg))
		ft_go_home(arg, env);
	else if (!ft_strncmp(arg, "~", 1))
		ft_go_home(arg, env);
	else if (!ft_strncmp(arg, "-", 1))
		ft_go_back(env);
	else
		ft_go_dir(arg);
	change_env_pwd(old_path, env);
	free(old_path);
}
