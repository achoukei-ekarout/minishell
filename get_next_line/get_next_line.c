/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:10:41 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/06 09:24:44 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_file(int fd, char **buf)
{
	int	bytes;

	bytes = read(fd, *buf, BUFFER_SIZE);
	if (bytes <= 0)
		return (bytes);
	(*buf)[bytes] = '\0';
	return (bytes);
}

char	*ft_replace(char *s1, char *s2)
{
	char	*new;

	if (!s2)
	{
		free(s1);
		return (NULL);
	}
	if (!*s2)
	{
		free(s1);
		free(s2);
		s2 = NULL;
		return (s2);
	}
	new = ft_strdup_gnl(s2);
	free(s1);
	free(s2);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*buf;
	char		*line;
	int			i;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (ft_strchr_gnl(temp, '\n') == -1)
	{
		bytes = read_file(fd, &buf);
		if (bytes <= 0)
			break ;
		temp = ft_strjoin_gnl(temp, buf);
	}
	i = ft_strchr_gnl(temp, '\n');
	if (i == -1)
		i = ft_strlen_gnl(temp);
	line = ft_substr_gnl(temp, 0, (size_t)(i + 1));
	temp = ft_replace(temp, ft_substr_gnl(temp, i + 1, ft_strlen_gnl(temp) - (i + 1)));
	return (free(buf), line);
}
