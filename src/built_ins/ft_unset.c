/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:09:54 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/17 17:31:53 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char *arg, t_env **env, t_exp **exp)
{
	char	**vars;
	int		i;

	vars = ft_split(arg, ' ');
	i = 0;
	while (vars[i])
	{
		env_unset(env, vars[i]);
		exp_unset(exp, vars[i]);
		free(vars[i]);
		i++;
	}
	free(vars);
}
