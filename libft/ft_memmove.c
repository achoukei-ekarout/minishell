/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:08:09 by ekarout           #+#    #+#             */
/*   Updated: 2025/11/03 14:53:42 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*cdest;
	const unsigned char	*csrc;
	int					i;

	cdest = (unsigned char *)dest;
	csrc = (const unsigned char *)src;
	i = n - 1;
	if (csrc < cdest && csrc + n - 1 >= cdest)
	{
		while (i >= 0)
		{
			cdest[i] = csrc[i];
			i--;
		}
	}
	else
		dest = (unsigned char *)ft_memcpy(cdest, csrc, n);
	return (dest);
}
