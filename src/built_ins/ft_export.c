/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:16:24 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/27 20:58:00 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_key(t_env **exp, char *key)
{
	if (!is_valid_key(key))
		return (export_key_error(key));
	if (find_key(exp, key))
		return (0);
	change_exp_value(exp, key, NULL);
	return (0);
}

int	ft_export_empty(t_env **exp, t_env **env, char *arg)
{
	char	*key;

	key = ft_substr(arg, 0, ft_strlen(arg) - 1);
	if (!is_valid_key(key))
	{
		export_key_error(key);
		free(key);
		return (-1);
	}
	change_exp_value(exp, key, "");
	change_env_value(env, key, "");
	free(key);
	return (0);
}

int	ft_export_key_value(t_env **exp, t_env **env, char *arg)
{
	char	**key_value;
	int		i;

	key_value = ft_split(arg, '=');
	if (!is_valid_key(key_value[0]))
		return (export_key_error(key_value[0]));
	change_exp_value(exp, key_value[0], key_value[1]);
	change_env_value(env, key_value[0], key_value[1]);
	i = -1;
	while (key_value[++i])
		free(key_value[i]);
	free(key_value);
	return (0);
}

int	ft_check_export(char *arg, t_env **exp, t_env **env)
{
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (export_key_error(arg));
	if (!ft_strchr(arg, '='))
		return (ft_export_key(exp, arg));
	if (ft_strlen(ft_strchr(arg, '=')) == 1)
		return (ft_export_empty(exp, env, arg));
	return (ft_export_key_value(exp, env, arg));
}

int	ft_export(char **argv, t_env **env, t_env **exp)
{
	int	i;
	int	result;

	if (ft_count_args(argv) == 1)
		return (ft_export_all(exp));
	i = 1;
	result = 0;
	while (argv[i])
	{
		if (ft_check_export(argv[i], exp, env) == -1)
			result = -1;
		i++;
	}
	return (result);
}
