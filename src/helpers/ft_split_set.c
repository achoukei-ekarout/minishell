/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:18:56 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/18 16:30:39 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	delimiter(char const *s, char *set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (i == 0 && !is_in_set(s[i], set))
			count++;
		while (is_in_set(s[i], set) && s[i])
		{
			if (!is_in_set(s[i + 1], set) && s[i + 1])
				count++;
			i++;
		}
		if (!s[i])
			break ;
		i++;
	}
	return (count);
}

static char	**allocation(char const *s, char *set, t_gc **head_gc)
{
	char	**result;

	result = (char **)allocate(head_gc,
			sizeof(char *) * (delimiter(s, set) + 1));
	if (!result)
		return (NULL);
	return (result);
}

char	**ft_split_set(char const *s, char *set, t_gc **head_gc)
{
	char			**result;
	unsigned int	i;
	int				j;
	int				k;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	result = allocation(s, set, head_gc);
	while (s[i])
	{
		while (is_in_set(s[i], set) && s[i])
			i++;
		j = i;
		if (!s[i])
			break ;
		while (!is_in_set(s[j], set) && s[j])
			j++;
		result[k] = ft_substr_allocate(s, i, j - i, head_gc);
		i = j;
		k++;
	}
	result[k] = 0;
	return (result);
}
