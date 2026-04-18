/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:42:55 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/18 16:15:08 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens->next)
	{
		tmp = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

int	ft_isempty(char	*arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] != '\f' && arg[i] != ' ' && arg[i] != '\t'
			&& arg[i] != '\n' && arg[i] != '\r' && arg[i] != '\v')
			break ;
		i++;
	}
	if (!arg[i])
		return (1);
	return (0);
}
