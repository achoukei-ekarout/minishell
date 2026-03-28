/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:08:53 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/27 18:02:10 by ekarout          ###   ########.fr       */
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

int	ft_count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	ft_cd(char **argv, t_env **env)
{
	char	*old_path;
	char	*arg;
	int		result;

	old_path = getcwd(NULL, 0);
	if (ft_count_args(argv) > 2)
		return (args_error("cd"));
	arg = argv[1];
	if (!arg)
		result = ft_go_home(arg, env);
	else if (!ft_strncmp(arg, "~", 1))
		result = ft_go_home(arg, env);
	else if (!ft_strncmp(arg, "-", 1))
		result = ft_go_back(env);
	else
		result = ft_go_dir(arg);
	if (result != -1)
		change_env_pwd(old_path, env);
	free(old_path);
	return (result);
}
