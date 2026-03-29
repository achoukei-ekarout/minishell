/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_mehods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:17:41 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/29 02:28:08 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_array(t_env **env, t_gc **head_gc)
{
	char	**envp;
	char	*temp;
	t_env	*curr;
	int		size;

	size = ft_env_size(*env);
	envp = (char **)allocate(head_gc, (size + 1) * sizeof(char *));
	size = 0;
	curr = *env;
	while (curr)
	{
		if (curr->data->value)
		{
			temp = ft_strjoin(curr->data->key, "=");
			envp[size] = ft_strjoin_allocate(temp, curr->data->value, head_gc);
			free(temp);
		}
		else
			envp[size] = ft_strdup_allocate(curr->data->key, head_gc);
		size++;
		curr = curr->next;
	}
	envp[size] = 0;
	return (envp);
}

void	env_unset(t_env **env, char *key)
{
	t_env	*curr;
	t_env	*next;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (!ft_strcmp(curr->data->key, key))
		{
			next = curr->next;
			// free(curr->data->key);
			// if (curr->data->value)
			// 	free(curr->data->value);
			// free(curr->data);
			// free(curr);
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

void	change_env_value(t_env **env, char *key, char *value, t_gc **perm_gc)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->data->key, key))
		{
			// if (curr->data->value)
			// 	free(curr->data->value);
			curr->data->value = ft_strdup_allocate(value, perm_gc);
			return ;
		}
		curr = curr->next;
	}
	add_new_node(env, key, value, perm_gc);
}

int	ft_env_size(t_env *env)
{
	int		count;
	t_env	*temp;

	count = 0;
	temp = env;
	while (temp)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}
