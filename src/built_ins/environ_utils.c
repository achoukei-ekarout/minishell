/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 22:12:24 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/05 22:50:48 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shlvl_value(char *s)
{
	int	level;

	level = ft_atoi(s);
	level++;
	free(s);
	s = ft_itoa(level);
	return (s);
}

char	*get_env_value(t_env **env, char *key)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->data->key, key))
			return (curr->data->value);
		curr = curr->next;
	}
	return (NULL);
}

t_env	*find_key(t_env **env, char	*key)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->data->key, key))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	add_new_node(t_env **env, char *key, char *value, t_gc **perm_gc)
{
	t_env	*node;

	node = env_new(key, value, perm_gc);
	env_add_back(env, node);
}

void	env_clear(t_env **env)
{
	t_env	*curr;
	t_env	*next;

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
