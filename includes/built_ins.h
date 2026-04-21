/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:06:29 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/18 16:54:23 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "data.h"
# include "garbage_collector.h"

int		ft_cd(char **argv, t_env **env, t_gc **perm_gc, t_vars *vars);
int		ft_go_home(char *dir, t_env **env, t_vars vars);
int		ft_go_back(t_env **env, t_vars vars);
int		ft_go_dir(char *dir, t_vars *vars);
int		ft_pwd(t_vars vars);
int		ft_env(t_env **env);
int		ft_unset(char **argv, t_env **env, t_env **exp);
int		ft_check_options(char *arg);
int		ft_remove_flag(char **argv);
void	ft_print(char **argv, int flag);
int		ft_echo(char **argv);
int		is_valid_key(char *key);
int		ft_exit(char **argv, t_garbage garbage, t_vars *vars);
int		is_numeric(char *arg);
int		ft_export(char	**argv, t_vars *vars, t_gc **perm_gc);
int		ft_check_export(char *arg, t_vars *vars, t_gc **perm_gc);
int		ft_export_key_value(t_vars *vars, char *arg, t_gc **perm_gc);
int		ft_export_empty(t_vars *vars, char *arg, t_gc **perm_gc);
int		ft_export_key(t_env **exp, char *key, t_gc **perm_gc, t_vars *vars);
int		ft_export_all(t_env **exp);
int		is_valid_key(char *key);
int		ft_count_args(char **argv);

#endif
