/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 23:24:47 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/13 23:41:07 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *arg)
{
	int	i;

	i = 0
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	print_exit_error(char *arg)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	ft_exit(char *arg, t_env **env)
{
	if (!arg)
		return (1);
	if (!is_numeric(arg))
	{
		print_exit_error(arg);
		change_env_value(env, "exit_code", "2");
		return (1);
	}
	change_env_value(env, "exit_code", arg);
	return (1);
}
