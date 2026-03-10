/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:06:29 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/09 02:12:59 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "data.h"

void	ft_cd(char *arg, t_env *env);
int		ft_isempty(char	*arg);
char	*ft_check_dir(char *arg, t_env *env);
char	*ft_go_home(char *dir, t_env *env);
char	*ft_go_back(char *dir, t_env *env);
char	*ft_go_dir(char *dir, t_env *env);
void	ft_pwd(t_env *env);
void	ft_env(t_env *env);
void	ft_unset(char *arg, t_env *env);

#endif
