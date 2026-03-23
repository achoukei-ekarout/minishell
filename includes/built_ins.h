/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:06:29 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/23 14:15:17 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "data.h"

void	ft_cd(char *arg, t_env **env);
int		ft_isempty(char	*arg);
void	ft_go_home(char *dir, t_env **env);
void	ft_go_back(t_env **env);
void	ft_go_dir(char *dir);
void	ft_pwd(t_env **env);
void	ft_env(t_env **env);
void	ft_unset(char *arg, t_env **env, t_env **exp);
int		ft_isspace(int c);
int		ft_check_options(char *arg);
char	*ft_remove_flag(char *arg);
void	ft_print(char *arg, int flag);
void	ft_echo(char *arg);
void	ft_export_key_error(char *key);
int		is_valid_key(char *key);
void	ft_exit(char *arg);
void	print_cd_error(char *dir);
void	print_exit_error(char *arg);
int		is_numeric(char *arg);
void	ft_export(char	*arg, t_env	**env, t_env **exp);
void	ft_check_export(char *arg, t_env **exp, t_env **env);
void	ft_export_key_value(t_env **exp, t_env **env, char *arg);
void	ft_export_empty(t_env **exp, t_env **env, char *arg);
void	ft_export_key(t_env **exp, char *key);
void	ft_export_all(t_env **exp);
int		is_valid_key(char *key);

#endif
