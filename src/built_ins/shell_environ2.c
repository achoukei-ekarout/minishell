/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_environ2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:12:13 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/17 18:28:56 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exp	*find_exp_key(t_exp **exp, char	*key)
{
	t_exp	*curr;

	curr = *exp;
	while (curr)
	{
		if (!ft_strcmp(curr->data->key, key))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	add_new_exp_node(t_exp **exp, char *key, char *value, int exported)
{
	t_exp	*node;

	node = exp_new(key, value, exported);
	ft_insert(exp, node);
}

void	exp_clear(t_exp **env)
{
	t_exp	*curr;
	t_exp	*next;

	curr = *env;
	while (curr)
	{
		next = curr->next;
		free(curr->data->key);
		free(curr->data->value);
		free(curr->data);
		free(curr);
		curr = next;
	}
	free(env);
}
