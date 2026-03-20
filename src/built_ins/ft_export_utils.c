/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 16:07:15 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/20 19:00:27 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key(char *key)
{
	int	i;

	i = -1;
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (key[++i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
	}
	return (1);
}
