/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 22:12:24 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/10 13:41:20 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	t_env	*curr;

	curr = env;
    while (curr)
    {
        if (!ft_strncmp(curr->data->key, key, ft_strlen(curr->data->key)))
            return (curr->data->value);
        curr = curr->next;
    }
    return NULL;
}

t_env	*find_key(t_env *env, char	*key)
{
	while (env)
	{
		if (!ft_strncmp(env->data->key, key, ft_strlen(env->data->key)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	change_env_value(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (!ft_strncmp(env->data->key, key, ft_strlen(env->data->key)))
		{
			free(env->data->value);
			env->data->value = ft_strdup(value);
		}
		env = env->next;
	}
}

void	env_clear(t_env *env)
{
	t_env	*curr;
	t_env	*next;

	curr = env;
	while (curr)
	{
		next = curr->next;
		free(curr->data->key);
		free(curr->data->value);
		free(curr->data);
		free(curr);
		curr = next;
	}
}

void	env_unset(t_env *env, char *key)
{
	t_env	*curr;
	t_env	*next;

	while (env)
	{
		if (!ft_strncmp(env->data->key, key, ft_strlen(env->data->key)))
		{
			free(env)
		}
		env = env->next;
	}
}
