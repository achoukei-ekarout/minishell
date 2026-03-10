/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:20:24 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/06 17:11:39 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits(long int n)
{
	long int	i;

	i = 0;
	if (n <= 0)
	{
		n = n * (-1);
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long int	nb;

	i = digits(n);
	str = (char *) ft_calloc ((i + 1), sizeof(char));
	if (!str)
		return (NULL);
	nb = n;
	if (nb < 0)
	{
		nb = nb * (-1);
		str[0] = '-';
	}
	while (--i >= 0 && str[i] != '-')
	{
		if (nb > 9)
		{
			str[i] = nb % 10 + '0';
			nb = nb / 10;
		}
		else if (nb < 10)
			str[i] = nb + '0';
	}
	return (str);
}
