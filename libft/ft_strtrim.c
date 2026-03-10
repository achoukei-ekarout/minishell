/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 19:49:23 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/10 13:47:24 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	is_trim(char s, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	j = ft_strlen((char *)s1) - 1;
	while (is_trim(s1[i], set))
		i++;
	if (!s1[i])
	{
		new = malloc(1);
		if (!new)
			return (NULL);
		new[0] = '\0';
		return (new);
	}
	while (is_trim(s1[j], set))
		j--;
	new = ft_substr(s1, i, (j - i + 1));
	return (new);
}
