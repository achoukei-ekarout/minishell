/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 01:55:01 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/13 02:18:14 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_export_data(t_env *node)
{
	char	*data;
	char	*temp;
	char	*key_value;

	if (node->data->value)
	{
		temp = ft_strjoin(node->data->key, "=");
		key_value = ft_strjoin(temp, "\"");
		free(temp);
		temp = ft_strjoin(key_value, node->data->value);
		free(key_value);
		key_value = ft_strjoin(temp, "\"");
		free(temp);
		data = ft_strjoin("declare -x ", key_value);
		free(key_value);
	}
	else
		data = ft_strjoin("declare -x ", node->data->key);
	return (data);
}

int	compare(t_exp **sorted_env, t_exp *curr, t_exp *prev, t_exp *node)
{
	if (ft_strcmp(node->data, curr->data) < 0)
	{
		if (!prev)
		{
			*sorted_env = node;
			node->next = curr;
			return (1);
		}
		prev->next = node;
		node->next = curr;
		return (1);
	}
	return (0);
}

void	ft_insert(t_exp **sorted_env, t_exp *node)
{
	t_exp	*curr;
	t_exp	*prev;

	if (!sorted_env || !*sorted_env)
	{
		*sorted_env = node;
		return ;
	}
	curr = *sorted_env;
	prev = NULL;
	while (curr)
	{
		if (compare(sorted_env, curr, prev, node))
			return ;
		prev = curr;
		curr = curr->next;
	}
	prev->next = node;
}

void	ft_export_all(t_env **env)
{
	t_exp	**sorted_env;
	t_exp	*sorted_curr;
	t_exp	*node;
	t_env	*curr;
	char	*data;

	sorted_env = (t_exp **)malloc(sizeof(t_env *));
	*sorted_env = NULL;
	curr = *env;
	while (curr)
	{
		data = ft_export_data(curr);
		node = exp_new(data);
		ft_insert(sorted_env, node);
		curr = curr->next;
	}
	sorted_curr = *sorted_env;
	while (sorted_curr)
	{
		printf("%s\n", sorted_curr->data);
		sorted_curr = sorted_curr->next;
	}
	ft_exp_clear(sorted_env);
}
