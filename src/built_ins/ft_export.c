/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:16:24 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/15 13:19:38 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_key(t_env **exp, char *key, t_gc **perm_gc, t_vars *vars)
{
	if (!is_valid_key(key))
		return (export_key_error(key, *vars));
	if (find_key(exp, key))
		return (0);
	change_exp_value(exp, key, NULL, perm_gc);
	return (0);
}

int	ft_export_empty(t_vars *vars, char *arg, t_gc **perm_gc)
{
	char	*key;

	key = ft_substr(arg, 0, ft_strlen(arg) - 1);
	if (!is_valid_key(key))
	{
		export_key_error(key, *vars);
		free(key);
		return (1);
	}
	change_exp_value(vars->exp, key, "", perm_gc);
	change_env_value(vars->env, key, "", perm_gc);
	free(key);
	return (0);
}

int	ft_export_key_value(t_vars *vars, char *arg, t_gc **perm_gc)
{
	char	**key_value;
	char	*key;
	char	*value;
	int		key_len;
	int		value_len;

	key_value = ft_split_allocate(arg, '=', perm_gc);
	if (!is_valid_key(key_value[0]))
		return (export_key_error(key_value[0], *vars));
	key = key_value[0];
	key_len = ft_strlen(key);
	value_len = ft_strlen(arg) - key_len - 1;
	value = ft_substr_allocate(arg, key_len + 1, value_len, perm_gc);
	change_exp_value(vars->exp, key, value, perm_gc);
	change_env_value(vars->env, key, value, perm_gc);
	return (0);
}

int	ft_check_export(char *arg, t_vars *vars, t_gc **perm_gc)
{
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (export_key_error(arg, *vars));
	if (!ft_strchr(arg, '='))
		return (ft_export_key(vars->exp, arg, perm_gc, vars));
	if (ft_strlen(ft_strchr(arg, '=')) == 1)
		return (ft_export_empty(vars, arg, perm_gc));
	return (ft_export_key_value(vars, arg, perm_gc));
}

int	ft_export(char **argv, t_vars *vars, t_gc **perm_gc)
{
	int	i;
	int	result;

	if (ft_count_args(argv) == 1)
		return (ft_export_all(vars->exp));
	i = 1;
	result = 0;
	while (argv[i])
	{
		if (ft_check_export(argv[i], vars, perm_gc) == 1)
			result = 1;
		i++;
	}
	return (result);
}
