/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:06:29 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/11 23:48:40 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "data.h"

void	ft_cd(char *arg, t_env **env);
int		ft_isempty(char	*arg);
void	ft_go_home(char *dir, t_env **env);
void	ft_go_dir(char *dir);
void	ft_pwd(t_env **env);
void	ft_env(t_env **env);
void	ft_unset(char *arg, t_env **env);
int		ft_isspace(int	c);
int 	ft_check_options(char *arg);
char	*ft_remove_flag(char *arg);
void	ft_print(char *arg, int flag);
void	ft_echo(char *arg);

#endif
