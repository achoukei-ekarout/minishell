/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:15:14 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/29 02:34:24 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new(char *key, char *value, t_gc **perm_gc)
{
	t_env	*node;

	node = allocate(perm_gc, sizeof(t_env));
	if (!node)
		return (NULL);
	node->data = allocate(perm_gc, sizeof(t_env_data));
	node->data->key = ft_strdup_allocate(key, perm_gc);
	node->data->value = ft_strdup_allocate(value, perm_gc);
	node->next = NULL;
	return (node);
}

t_env	*create_env_node(char *s, t_gc **perm_gc)
{
	char	**key_value;
	t_env	*node;
	int		i;
	int		level;

	key_value = ft_split(s, '=');
	if (!key_value)
		return (NULL);
	if (!ft_strcmp(key_value[0], "SHLVL"))
	{
		level = ft_atoi(key_value[1]);
		level++;
		free(key_value[1]);
		key_value[1] = ft_itoa(level);
	}
	node = env_new(key_value[0], key_value[1], perm_gc);
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

t_env	**environ_init(char **envp, t_gc **perm_gc)
{
	t_env	**env;
	t_env	*node;
	int		i;

	env = (t_env **)allocate(perm_gc, sizeof(t_env *));
	*env = NULL;
	i = 0;
	while (envp[i])
	{
		node = create_env_node(envp[i], perm_gc);
		env_add_back(env, node);
		i++;
	}
	return (env);
}

void	vars_init(t_vars *vars, char **envp, t_gc **perm_gc)
{
	vars->env = environ_init(envp, perm_gc);
	vars->exp = exp_init(vars->env, perm_gc);
	vars->exit_code = 0;
}
