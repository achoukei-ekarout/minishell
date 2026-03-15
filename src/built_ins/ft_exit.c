/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 23:24:47 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/15 04:04:59 by ekarout          ###   ########.fr       */
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
	if(arg[i] == '+' || arg[i] == '-')
	{
		if(arg[i] == '-')
			sign = -1;
		i++;
	}
	while (arg[i])
	{
		if(!ft_isdigit(arg[i]))
			return (-1);
		result = (result * 10 + (arg[i] - '0')) % 256;
		i++;
	}
	if (sign == -1)
		result = (256 - result) % 256;
	return (result);
}

void	ft_exit(char *arg)
{
	int	exit_code;

	exit_code = 0;
	if (!arg)
		exit(exit_code);
	exit_code = exit_status_code(arg);
	ft_putstr_fd("exit\n", 2);
	if (exit_code == -1)
	{
		print_exit_error(arg);
		exit_code = 2;
	}
	if (ft_strlen(arg) > 9)
	{
		print_exit_error(arg);
		exit_code = 2;
	}
	if (ft_strlen(arg) == 9 && ft_strcmp(arg, "9223372036854775807") < 0)
	{
		print_exit_error(arg);
		exit_code = 2;
	}
	exit(exit_code);
}
