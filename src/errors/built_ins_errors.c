/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:34:20 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/08 11:05:40 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_error(char *arg)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (2);
}

int	cd_dir_error(char *dir, t_vars vars)
{
	ft_putstr_fd(vars.executer_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

int	args_error(char *fn, t_vars vars)
{
	ft_putstr_fd(vars.executer_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(fn, 2);
	ft_putstr_fd(": too many arguments\n", 2);
	return (1);
}

int	export_key_error(char *key, t_vars vars)
{
	ft_putstr_fd(vars.executer_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}
