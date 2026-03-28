/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_allocate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:57:18 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/28 23:24:30 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	delimiter(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			count++;
		while (s[i] == c)
		{
			if (s[i + 1] != c && s[i + 1])
				count++;
			i++;
		}
		if (!s[i])
			break ;
		i++;
	}
	return (count);
}

static char	**allocation(char const *s, char c, t_gc **head_gc)
{
	char	**result;

	result = (char **)allocate(head_gc, sizeof(char *) * (delimiter(s, c) + 1));
	if (!result)
		return (NULL);
	return (result);
}

char	**ft_split_allocate(char const *s, char c, t_gc **head_gc)
{
	char			**result;
	unsigned int	i;
	int				j;
	int				k;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	result = allocation(s, c, head_gc);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		if (!s[i])
			break ;
		while (s[j] != c && s[j])
			j++;
		result[k] = ft_substr_allocate(s, i, j - i, head_gc);
		i = j;
		k++;
	}
	result[k] = NULL;
	return (result);
}
