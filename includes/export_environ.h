/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_environ.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:11:24 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/28 20:34:30 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_ENVIRON_H
# define EXPORT_ENVIRON_H

# include "data.h"
# include "garbage_collector.h"

void	change_exp_value(t_env **exp, char *key, char *value, t_gc **perm_gc);
int		compare(t_env **exp, t_env *curr, t_env *prev, t_env *node);
void	ft_insert(t_env **exp, t_env *node);
t_env	**exp_init(t_env **env, t_gc **perm_gc);

#endif
