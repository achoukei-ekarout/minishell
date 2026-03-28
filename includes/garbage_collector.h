/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 21:23:55 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/28 23:24:30 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

typedef struct e_gc
{
	void		*value;
	struct e_gc	*next;
}				t_gc;

void			*allocate(t_gc **head, size_t size);
t_gc			*create_gc_node(void *ptr);
char			*ft_strdup_allocate(const char *s, t_gc **head);
void			free_garbage(t_gc **head);
char			*ft_substr_allocate(char const *s, unsigned int start,
					size_t len, t_gc **head_gc);
char			**ft_split_allocate(char const *s, char c, t_gc **head_gc);
char			*ft_strjoin_allocate(char const *s1, char const *s2,
					t_gc **head_gc);

#endif