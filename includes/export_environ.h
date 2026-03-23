/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_environ.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:11:24 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/23 14:40:14 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_ENVIRON_H
# define EXPORT_ENVIRON_H

# include "data.h"

void	change_exp_value(t_env **exp, char *key, char *value);
int		compare(t_env **exp, t_env *curr, t_env *prev, t_env *node);
void	ft_insert(t_env **exp, t_env *node);
t_env	**exp_init(t_env **env);

#endif
