/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:08:53 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/18 16:14:02 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env_pwd(char *old_path, t_env **env, t_gc **perm_gc)
{
	char	*new_path;

	new_path = getcwd(NULL, 0);
	change_env_value(env, "OLDPWD", old_path, perm_gc);
	change_env_value(env, "PWD", new_path, perm_gc);
	free(new_path);
}

int	ft_count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	ft_cd(char **argv, t_env **env, t_gc **perm_gc, t_vars *vars)
{
	char	*old_path;
	char	*arg;
	int		result;

	old_path = getcwd(NULL, 0);
	if (ft_count_args(argv) > 2)
	{
		free(old_path);
		return (args_error("cd", *vars));
	}
	arg = argv[1];
	if (!arg)
		result = ft_go_home(arg, env, *vars);
	else if (!ft_strncmp(arg, "-", 1))
		result = ft_go_back(env, *vars);
	else
		result = ft_go_dir(arg, vars);
	if (result != -1)
		change_env_pwd(old_path, env, perm_gc);
	free(old_path);
	return (result);
}
