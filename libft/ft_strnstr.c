/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:33:05 by ekarout           #+#    #+#             */
/*   Updated: 2025/11/10 11:18:24 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	iter(char *big, char *sub, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	c;

	i = 0;
	c = 0;
	while (big[i] && i <= len && sub[0])
	{
		c = i;
		j = 0;
		while (big[i] == sub[j] && i < len)
		{
			i++;
			j++;
			if (sub[j] == '\0')
				return (c + 1);
		}
		i = c;
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *sub, size_t len)
{
	int		c;
	char	*cbig;
	char	*csub;

	cbig = (char *)big;
	csub = (char *)sub;
	if (big == NULL || sub == NULL)
		return (NULL);
	if (!csub[0])
		return (cbig);
	if (len == 0)
		return (0);
	c = iter(cbig, csub, len);
	if (c)
		return (cbig + c - 1);
	return (0);
}
