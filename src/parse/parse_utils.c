/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 23:12:08 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/21 10:26:48 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_argv(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

char	**ft_join_argv(char **args, char *value)
{
	int		args_len;
	char	**new_args;
	int		i;

	i = 0;
	args_len = ft_strlen_argv(args);
	new_args = malloc(sizeof(char *) * (args_len + 2));
	if (args_len == 0)
	{
		new_args[0] = ft_strdup(value);
		new_args[1] = NULL;
		return (new_args);
	}
	while (args[i])
	{
		new_args[i] = ft_strdup(args[i]);
		i++;
	}
	new_args[i] = ft_strdup(value);
	new_args[++i] = NULL;
	return (new_args);
}
