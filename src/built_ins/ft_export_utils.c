/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 16:07:15 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/13 03:31:21 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exp	*exp_new(char *data)
{
	t_exp	*node;

	node = malloc(sizeof(t_exp));
	if (!node)
		return (NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}

void	ft_exp_clear(t_exp **sorted_env)
{
	t_exp	*curr;
	t_exp	*next;

	if (!sorted_env || !*sorted_env)
		return ;
	curr = *sorted_env;
	while (curr)
	{
		next = curr->next;
		free(curr->data);
		free(curr);
		curr = next;
	}
	free(sorted_env);
}

int	is_valid_key(char *key)
{
	int i;

	i = -1;
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (key[++i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
	}
	return (1);
}

void	ft_key_error(char *key)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}
