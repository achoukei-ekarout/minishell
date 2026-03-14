/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:17:00 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/14 17:45:39 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		i;
	char	*args;

	i = -1;
	args = ft_strtrim(arg, " \n\t\r\v\f");
	while (args[++i])
	{
		if (args[i] == '\\')
			continue ;
		if (ft_isspace(args[i]))
		{
			while (ft_isspace(args[i]))
				i++;
			ft_putchar_fd(' ', 1);
			i--;
			continue ;
		}
		ft_putchar_fd(args[i], 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	free(args);
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
