/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 23:24:47 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/04 21:06:59 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status_code(char *arg)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			sign = -1;
		i++;
	}
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (-1);
		result = (result * 10 + (arg[i] - '0')) % 256;
		i++;
	}
	if (sign == -1)
		result = (256 - result) % 256;
	return (result);
}

void	exit_shell(int exit_code, t_gc **gc, t_gc **perm_gc)
{
	free_garbage(gc);
	free_garbage(perm_gc);
	exit(exit_code);
}

int	ft_exit(char **argv, t_gc **gc, t_gc **perm_gc, t_vars *vars)
{
	int		exit_code;
	char	*arg;

	exit_code = 0;
	ft_putstr_fd("exit\n", 1);
	if (ft_count_args(argv) > 2)
		return (args_error("exit", *vars));
	arg = argv[1];
	if (!arg)
		exit_shell(exit_code, gc, perm_gc);
	exit_code = exit_status_code(arg);
	if (exit_code == -1)
		exit_code = exit_error(arg);
	if (ft_strlen(arg) > 19)
		exit_code = exit_error(arg);
	if (ft_strlen(arg) == 19 && ft_strcmp(arg, "9223372036854775807") < 0)
		exit_code = exit_error(arg);
	exit_shell(exit_code, gc, perm_gc);
	return (0);
}
