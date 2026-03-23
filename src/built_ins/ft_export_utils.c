/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 16:07:15 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/23 14:42:15 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key(char *key)
{
	int	i;

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

void	change_exp_value(t_env **exp, char *key, char *value)
{
	t_env	*curr;

	curr = *exp;
	while (curr)
	{
		if (!ft_strcmp(curr->data->key, key))
		{
			if (curr->data->value)
				free(curr->data->value);
			curr->data->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	curr = env_new(key, value);
	ft_insert(exp, curr);
}

int	compare(t_env **exp, t_env *curr, t_env *prev, t_env *node)
{
	if (ft_strcmp(node->data->key, curr->data->key) < 0)
	{
		if (!prev)
		{
			*exp = node;
			node->next = curr;
			return (1);
		}
		prev->next = node;
		node->next = curr;
		return (1);
	}
	return (0);
}

void	ft_insert(t_env **exp, t_env *node)
{
	t_env	*curr;
	t_env	*prev;

	if (!exp || !*exp)
	{
		*exp = node;
		return ;
	}
	curr = *exp;
	prev = NULL;
	while (curr)
	{
		if (compare(exp, curr, prev, node))
			return ;
		prev = curr;
		curr = curr->next;
	}
	prev->next = node;
}

t_env	**exp_init(t_env **env)
{
	t_env	**exp;
	t_env	*exp_node;
	t_env	*curr_env;

	exp = (t_env **)malloc(sizeof(t_env *));
	*exp = NULL;
	curr_env = *env;
	while (curr_env)
	{
		exp_node = env_new(curr_env->data->key, curr_env->data->value);
		ft_insert(exp, exp_node);
		curr_env = curr_env->next;
	}
	return (exp);
}
