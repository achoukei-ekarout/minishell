/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_allocate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 01:00:55 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/28 23:24:30 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_allocate(const char *s, t_gc **head)
{
	char	*new;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	new = allocate(head, (len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_substr_allocate(char const *s, unsigned int start, size_t len,
		t_gc **head_gc)
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
	sub = (char *)allocate(head_gc, (len + 1) * sizeof(char));
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

char	*ft_strjoin_allocate(char const *s1, char const *s2, t_gc **head_gc)
{
	char	*new;
	int		len;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	i = 0;
	new = (char *)allocate(head_gc, len * sizeof(char));
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
