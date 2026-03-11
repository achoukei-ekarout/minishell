/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:15:14 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/11 23:08:25 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_node(t_env **env, char *key, char *value)
{
	t_env	*node;

	node = env_new(key, value);
	env_add_back(env, node);
}

t_env	*env_new(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->data = malloc(sizeof(t_env_data));
	node->data->key = ft_strdup(key);
	node->data->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

t_env	*create_env_node(char *s)
{
	char	**key_value;
	t_env	*node;
	int		i;

	key_value = ft_split(s, '=');
	if (!key_value)
		return (NULL);
	node = env_new(key_value[0], key_value[1]);
	i = 0;
	while (key_value[i])
	{
		free(key_value[i]);
		i++;
	}
	free(key_value);
	return (node);
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!env || !*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	**environ_init(char **envp)
{
	t_env	**env;
	t_env	*node;
	int		i;

	env = (t_env **)malloc(sizeof(t_env *));
	*env = NULL;
	i = 0;
	while (envp[i])
	{
		node = create_env_node(envp[i]);
		env_add_back(env, node);
		i++;
	}
	return (env);
}
