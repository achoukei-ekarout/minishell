/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:17:00 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/27 18:02:34 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_options(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	if (i == 1)
		return (0);
	return (1);
}

int	ft_remove_flag(char **argv)
{
	int	i;
	int	flags;

	i = 2;
	flags = 1;
	while (argv[i])
	{
		if (!ft_check_options(argv[i]))
			return (flags);
		i++;
		flags++;
	}
	return (flags);
}

void	ft_print(char **argv, int flag)
{
	int	i;
	int	j;

	i = flag;
	while (argv[++i])
	{
		if (i != flag + 1)
			ft_putchar_fd(' ', 1);
		j = 0;
		while (argv[i][j])
		{
			ft_putchar_fd(argv[i][j], 1);
			j++;
		}
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
}

int	ft_echo(char **argv)
{
	int	flag;

	if (!argv[1])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	flag = ft_check_options(argv[1]);
	if (flag)
		ft_print(argv, ft_remove_flag(argv));
	else
		ft_print(argv, 0);
	return (0);
}
