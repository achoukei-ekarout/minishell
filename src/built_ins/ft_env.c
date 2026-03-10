/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:09:32 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/10 16:18:57 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (curr->data->value)
			printf("%s=%s\n", curr->data->key, curr->data->value);
		else
			printf("%s\n", curr->data->key);
		curr = curr->next;
	}
}