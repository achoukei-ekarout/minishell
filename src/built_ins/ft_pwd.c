/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:04:09 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/07 11:33:27 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd()
{
	char	*pathname;

	pathname = getcwd(NULL, 0);
	if (!pathname)
	{
		perror("getcwd");
		return (1);
	}
	printf("%s\n", pathname);
	free(pathname);
	return (0);
}
