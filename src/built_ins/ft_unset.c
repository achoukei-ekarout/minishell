/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:09:54 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/08 00:55:28 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char *arg, t_env *env)
{
	char	**vars;
	int		i;
	
	vars = ft_split(arg, ' ');
	i = 0;
	while (vars[i])
	{
		env_unset(env, vars[i]);
		i++;
	}
}
