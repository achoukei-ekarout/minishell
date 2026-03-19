/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_environ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:43:10 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/17 19:04:46 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exp_unset(t_exp **env, char *key)
{
	t_exp	*curr;
	t_exp	*next;
	t_exp	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (!ft_strcmp(curr->data->key, key))
		{
			next = curr->next;
			free(curr->data->key);
			if (curr->data->value)
				free(curr->data->value);
			free(curr->data);
			free(curr);
			if (prev)
				prev->next = next;
			else
				*env = next;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	change_exp_value(t_exp **exp, t_env **env, char *key, char *value, int exported)
{
	t_exp	*curr;

	curr = *exp;
	if (value)
		change_env_value(env, key, value);
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
	add_new_exp_node(exp, key, value, exported);
}

int	compare(t_exp **exp, t_exp *curr, t_exp *prev, t_exp *node)
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

void	ft_insert(t_exp **exp, t_exp *node)
{
	t_exp	*curr;
	t_exp	*prev;

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

t_exp	*exp_new(char *key, char *value, int exported)
{
	t_exp	*node;

	node = malloc(sizeof(t_exp));
	if (!node)
		return (NULL);
	node->data = malloc(sizeof(t_exp_data));
	node->data->key = ft_strdup(key);
	node->data->value = ft_strdup(value);
	node->data->exported = exported;
	node->next = NULL;
	return (node);
}

t_exp	**exp_init(t_env **env)
{
	t_exp	**exp;
	t_exp	*exp_node;
	t_env	*curr_env;

	exp = (t_exp **)malloc(sizeof(t_exp *));
	*exp = NULL;
	curr_env = *env;
	while (curr_env)
	{
		exp_node = exp_new(curr_env->data->key, curr_env->data->value, 1);
		ft_insert(exp, exp_node);
		curr_env = curr_env->next;
	}
	return (exp);
}
