/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:09:32 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/08 00:35:51 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (curr->exported)
		{
			if (curr->value)
				printf("%s=%s\n", curr->key, curr->value);
			else
				printf("%s\n", curr->key);
		}
		curr = curr->next;
	}
}