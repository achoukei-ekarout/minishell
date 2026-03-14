/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:16:24 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/14 17:29:19 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_key(t_env **env, char *key)
{
	if(!is_valid_key(key))
	{
		ft_export_key_error(key);
		return ;
	}
	if(find_key(env, key))
		return ;
	change_env_value(env, key, NULL);
}

void	ft_export_empty(t_env **env, char *arg)
{
	char	*key;

	key = ft_substr(arg, 0, ft_strlen(arg) - 1);
	if(!is_valid_key(key))
	{
		ft_export_key_error(key);
		free(key);
		return ;
	}
	change_env_value(env, key, "");
	free(key);
}

void	ft_export_key_value(t_env **env, char *arg)
{
	char	**key_value;
	int		i;

	key_value = ft_split(arg, '=');
	if(!is_valid_key(key_value[0]))
		ft_export_key_error(key_value[0]);
	else
		change_env_value(env, key_value[0], key_value[1]);
	i = -1;
	while(key_value[++i])
		free(key_value[i]);
	free(key_value);
}

void	ft_check_export(char *arg, t_env **env)
{
	if(!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_export_key_error(arg);
		return ;
	}
	if(!ft_strchr(arg, '='))
		ft_export_key(env, arg);
	else if(ft_strlen(ft_strchr(arg, '=')) == 1)
		ft_export_empty(env, arg);
	else
		ft_export_key_value(env, arg);
}

void	ft_export(char	*arg, t_env	**env)
{
	char	**args;
	int		i;

	if (!arg || !*arg)
	{
		ft_export_all(env);
		return ;
	}
	args = ft_split(arg, ' ');
	i = 0;
	while (args[i])
	{
		ft_check_export(args[i], env);
		free(args[i]);
		i++;
	}
	free(args);
}	
