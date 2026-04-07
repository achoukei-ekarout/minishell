/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:11:14 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/06 09:25:52 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*new;
	int		len;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup_gnl(s2));
	if (!s2)
		return (s1);
	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	i = -1;
	j = 0;
	new = (char *)malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}

char	*ft_strdup_gnl(char *s)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	if (!s)
		return (ft_strdup_gnl(""));
	len = ft_strlen_gnl(s);
	new = (char *)malloc((len + 1) * sizeof(char));
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

int	ft_strchr_gnl(char *s, int c)
{
	int		i;
	char	*str;

	if (!s)
		return (-1);
	i = 0;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	j;
	size_t	l;

	j = 0;
	l = ft_strlen_gnl(s);
	if (start >= l)
		return (NULL);
	if (start + len > l)
		len = l - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (s[start + j] && j < len)
	{
		sub[j] = s[start + j];
		j++;
	}
	sub[j] = '\0';
	return (sub);
}
