/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:09:03 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/28 18:36:53 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# include "data.h"
# include "garbage_collector.h"

t_env		*env_new(char *key, char *value, t_gc **perm_gc);
t_env		*create_env_node(char *s, t_gc **perm_gc);
void		env_add_back(t_env **env, t_env *new);
t_env		**environ_init(char **envp, t_gc **perm_gc);
char		*get_env_value(t_env **env, char *key);
t_env		*find_key(t_env **env, char	*key);
void		change_env_value(t_env **env, char *key, char *value, t_gc **perm_gc);
void		env_clear(t_env **env);
void		env_unset(t_env **env, char *key);
void		add_new_node(t_env **env, char *key, char *value, t_gc **perm_gc);
char		**env_to_array(t_env **env, t_gc **head_gc);
int			ft_env_size(t_env *env);
void		vars_init(t_vars *vars, char **envp, t_gc **perm_gc);

#endif