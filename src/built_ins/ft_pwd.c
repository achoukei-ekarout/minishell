/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:04:09 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/11 01:24:22 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_vars vars)
{
	char	*pathname;

	pathname = getcwd(NULL, 0);
	if (!pathname)
	{
		ft_putstr_fd(vars.executer_name, 2);
		ft_putstr_fd(": ", 2);
		perror("getcwd");
		return (1);
	}
	printf("%s\n", pathname);
	free(pathname);
	return (0);
}
