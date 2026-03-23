/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:52:04 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/23 16:16:46 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_arr(char ***arr)
{
	int	i;

	i = 0;
	if (!(*arr))
		return (NULL);
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	return (NULL);
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}
