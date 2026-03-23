/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 22:12:24 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/17 17:22:35 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env **env, char *key)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if (!ft_strncmp(curr->data->key, key, ft_strlen(curr->data->key)))
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

void	add_new_node(t_env **env, char *key, char *value)
{
	t_env	*node;

	node = env_new(key, value);
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
