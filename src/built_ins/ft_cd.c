/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:08:53 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/09 02:12:17 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isempty(char	*arg)
{
	int	i;

	i = 0;
	while(arg[i])
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

char	*ft_check_dir(char *arg, t_env *env)
{
	char	*path;

	if(ft_isempty(arg))
		path = ft_go_home(arg, env);
	else if (!ft_strncmp(arg, "~", 1))
		path = ft_go_home(arg, env);
	else if(!ft_strncmp(arg, "..", 2))
		path = ft_go_back(arg, env);
	else
		path = ft_go_dir(arg, env);
	return (path);
}

void	ft_cd(char *arg, t_env *env)
{
	char	*path;

	path = ft_check_dir(arg, env);
	if (!path)
		return ;
	change_env_value(env, "PWD", path);
}
