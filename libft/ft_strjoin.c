/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:57:46 by ekarout           #+#    #+#             */
/*   Updated: 2025/11/10 09:36:05 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		len;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	i = 0;
	new = (char *)malloc(len * sizeof(char));
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[i - ft_strlen((char *)s1)])
	{
		new[i] = s2[i - ft_strlen((char *)s1)];
		i++;
	}
	new[i] = '\0';
	return (new);
}
