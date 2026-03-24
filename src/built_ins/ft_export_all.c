/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 01:55:01 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/24 13:11:49 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_all(t_env **exp)
{
	t_env	*curr;

	curr = *exp;
	while (curr)
	{
		if (curr->data->value)
		{
			printf("declare -x ");
			printf("%s=\"%s\"\n", curr->data->key, curr->data->value);
		}
		else
			printf("declare -x %s\n", curr->data->key);
		curr = curr->next;
	}
	return (0);
}
