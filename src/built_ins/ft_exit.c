/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 23:24:47 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/11 00:57:25 by ekarout          ###   ########.fr       */
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

void	exit_shell(int exit_code, t_garbage garbage, char *input)
{
	if (input)
		free(input);
	free_garbage(garbage.temp_gc);
	free_garbage(garbage.perm_gc);
	rl_clear_history();
	exit(exit_code);
}

int	valid_exit_code(char *arg)
{
	if (ft_strlen(arg) > 20)
		return (0);
	if (ft_strlen(arg) >= 19 && ft_strncmp(arg, "922337203685477580", 18) > 0)
		return (0);
	if (ft_strlen(arg) == 20 && ft_strncmp(arg, "-922337203685477580", 19) > 0)
		return (0);
	if (ft_strlen(arg) >= 19 && !ft_strncmp(arg, "922337203685477580", 18))
	{
		if (arg[18] > '7')
			return (0);
	}
	if (ft_strlen(arg) == 20 && !ft_strncmp(arg, "-922337203685477580", 19))
	{
		if (arg[19] > '8')
			return (0);
	}
	return (1);
}

int	ft_exit(char **argv, t_garbage garbage, t_vars *vars)
{
	int		exit_code;
	char	*arg;

	exit_code = 0;
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 1);
	if (ft_count_args(argv) > 2)
		return (args_error("exit", *vars));
	arg = argv[1];
	if (!arg)
		exit_shell(exit_code, garbage, vars->input);
	if (!valid_exit_code(arg))
		exit_code = exit_error(arg, *vars);
	else
		exit_code = exit_status_code(arg);
	if (exit_code == -1)
		exit_code = exit_error(arg, *vars);
	exit_shell(exit_code, garbage, vars->input);
	return (0);
}
