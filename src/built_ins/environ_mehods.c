/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_mehods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:17:41 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/14 13:50:16 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_array(t_env **env)
{
	char	**envp;
	char	*temp;
	t_env	*curr;
	int		size;

	size = ft_env_size(*env);
	envp = (char **)malloc((size + 1) * sizeof(char *));
	size = 0;
	curr = *env;
	while (curr)
	{
		if(curr->data->value)
		{
			temp = ft_strjoin(curr->data->key, "=");
			envp[size] = ft_strjoin(temp, curr->data->value);
			free(temp);
		}
		else
			envp[size] = ft_strdup(curr->data->key);
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
	while (curr)
	{
		if (!ft_strncmp(curr->data->key, key, ft_strlen(curr->data->key)))
		{
			next = curr->next;
			free(curr->data->key);
			free(curr->data->value);
			free(curr->data);
			free(curr);
			prev->next = next;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	change_env_value(t_env **env, char *key, char *value)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if (!ft_strncmp(curr->data->key, key, ft_strlen(curr->data->key)))
		{
			if (curr->data->value)
				free(curr->data->value);
			curr->data->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	add_new_node(env, key, value);
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
