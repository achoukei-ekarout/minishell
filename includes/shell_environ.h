/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_environ.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:33:08 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/20 19:45:21 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_ENVIRON_H
# define SHELL_ENVIRON_H

# include "data.h"

t_exp	**exp_init(t_env **env);
t_exp	*exp_new(char *key, char *value, int exported);
void	ft_insert(t_exp **exp, t_exp *node);
int		compare(t_exp **exp, t_exp *curr, t_exp *prev, t_exp *node);
void	change_exp_value(t_exp **exp, t_env **env, char *key, char *value, int exported);
void	exp_unset(t_exp **env, char *key);
t_exp	*find_exp_key(t_exp **exp, char	*key);
void	add_new_exp_node(t_exp **exp, char *key, char *value, int exported);
void	exp_clear(t_exp **env);

#endif