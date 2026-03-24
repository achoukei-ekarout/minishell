/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:09:54 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/24 16:24:56 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **argv, t_env **env, t_env **exp)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		env_unset(env, argv[i]);
		env_unset(exp, argv[i]);
		i++;
	}
	return (0);
}
