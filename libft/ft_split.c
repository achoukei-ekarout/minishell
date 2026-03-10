/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 21:59:54 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/06 16:41:08 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	delimiter(char const *s, char c)
{
	int		i;
	int		count;

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

static char	**allocation(char const *s, char c)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * (delimiter(s, c) + 1));
	if (!result)
		return (NULL);
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char			**result;
	unsigned int	i;
	int				j;
	int				k;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	result = allocation(s, c);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		if (!s[i])
			break ;
		while (s[j] != c && s[j])
			j++;
		result[k] = ft_substr(s, i, j - i);
		i = j;
		k++;
	}
	result[k] = NULL;
	return (result);
}
