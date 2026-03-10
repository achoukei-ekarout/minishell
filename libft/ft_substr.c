/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:45:36 by ekarout           #+#    #+#             */
/*   Updated: 2025/11/10 11:08:27 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;
	size_t	l;

	i = start;
	j = 0;
	l = ft_strlen(s);
	if (i > l)
		i = l;
	if (i + len > l)
		len = l - i;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (s[i + j] && j < len)
	{
		sub[j] = s[i + j];
		j++;
	}
	sub[j] = '\0';
	return (sub);
}
