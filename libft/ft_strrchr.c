/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:25:47 by ekarout           #+#    #+#             */
/*   Updated: 2025/11/04 18:08:32 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	l;
	int	i;

	l = 0;
	while (str[l])
		l++;
	i = l - 1;
	while (i >= 0)
	{
		if (str[i] == (c % 128))
			return ((char *)str + (i));
		i--;
	}
	if (!(c % 128))
		return ((char *)str + l);
	return (0);
}
