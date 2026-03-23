/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_allocate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 01:00:55 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/23 03:01:26 by achoukei         ###   ########.fr       */
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

static int	delimiter(char const *s, char c)
{
	int	i;
	int	count;

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

static char	**allocation(char const *s, char c, t_gc **head_gc)
{
	char	**result;

	result = (char **)allocate(head_gc, sizeof(char *) * (delimiter(s, c) + 1));
	if (!result)
		return (NULL);
	return (result);
}

char	**ft_split_allocate(char const *s, char c, t_gc **head_gc)
{
	char			**result;
	unsigned int	i;
	int				j;
	int				k;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	result = allocation(s, c, head_gc);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		if (!s[i])
			break ;
		while (s[j] != c && s[j])
			j++;
		result[k] = ft_substr_allocate(s, i, j - i, head_gc);
		i = j;
		k++;
	}
	result[k] = NULL;
	return (result);
}
