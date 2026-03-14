/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:06:29 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/14 17:31:37 by ekarout          ###   ########.fr       */
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
void	ft_unset(char *arg, t_env **env);
int		ft_isspace(int c);
int		ft_check_options(char *arg);
char	*ft_remove_flag(char *arg);
void	ft_print(char *arg, int flag);
void	ft_echo(char *arg);
void	ft_export(char	*arg, t_env	**env);
void	ft_export_all(t_env **env);
void	ft_check_export(char *arg, t_env **env);
void	ft_export_key_value(t_env **env, char *arg);
void	ft_export_empty(t_env **env, char *arg);
void	ft_export_key(t_env **env, char *key);
void	ft_export_key_error(char *key);
int		is_valid_key(char *key);
void	ft_insert(t_exp **sorted_env, t_exp *node);
char	*ft_export_data(t_env *node);
t_exp	*exp_new(char *data);
void	ft_exp_clear(t_exp **sorted_env);
int		compare(t_exp **sorted_env, t_exp *curr, t_exp *prev, t_exp *node);
int		ft_exit(char *arg, t_env **env);
void	print_cd_error(char *dir);
void	print_exit_error(char *arg);
int		is_numeric(char *arg);
int		ft_env_size(t_env *env);

#endif
