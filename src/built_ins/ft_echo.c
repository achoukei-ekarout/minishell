/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:17:00 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/12 01:47:08 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n')
		return (1);
	if (c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_check_options(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '-')
		{
			i++;
			if (arg[i] == 'n')
				return (1);
		}
		if (!ft_isspace(arg[i]))
			return (0);
		i++;
	}
	return (0);
}

char	*ft_remove_flag(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '-')
		{
			while (arg[i])
			{
				i++;
				if (!ft_isspace(arg[i]) && arg[i] != '-' && arg[i] != 'n')
					break ;
			}
		}
		if (!ft_isspace(arg[i]))
			break ;
		i++;
	}
	return (arg + i);
}

void	ft_print(char *arg, int flag)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '\\')
			continue ;
		if (ft_isspace(arg[i]))
		{
			while (ft_isspace(arg[i]))
				i++;
			ft_putchar_fd(' ', 1);
			i--;
			continue ;
		}
		ft_putchar_fd(arg[i], 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
}

void	ft_echo(char *arg)
{
	int	flag;

	flag = ft_check_options(arg);
	if (flag)
		ft_print(ft_remove_flag(arg), 1);
	else
		ft_print(arg, 0);
}
