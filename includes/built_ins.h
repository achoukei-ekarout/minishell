/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:06:29 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/28 20:37:27 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "data.h"
# include "garbage_collector.h"

int		ft_cd(char **argv, t_env **env, t_gc **perm_gc);
int		ft_isempty(char	*arg);
int		ft_go_home(char *dir, t_env **env);
int		ft_go_back(t_env **env);
int		ft_go_dir(char *dir);
int		ft_pwd(t_env **env);
int		ft_env(t_env **env);
int		ft_unset(char **argv, t_env **env, t_env **exp);
int		ft_check_options(char *arg);
int		ft_remove_flag(char **argv);
void	ft_print(char **argv, int flag);
int		ft_echo(char **argv);
int		is_valid_key(char *key);
int		ft_exit(char **argv);
int		is_numeric(char *arg);
int		ft_export(char	**argv, t_env	**env, t_env **exp, t_gc **perm_gc);
int		ft_check_export(char *arg, t_env **exp, t_env **env, t_gc **perm_gc);
int		ft_export_key_value(t_env **exp, t_env **env, char *arg, t_gc **perm_gc);
int		ft_export_empty(t_env **exp, t_env **env, char *arg, t_gc **perm_gc);
int		ft_export_key(t_env **exp, char *key, t_gc **perm_gc);
int		ft_export_all(t_env **exp);
int		is_valid_key(char *key);
int		exit_error(char *arg);
int		cd_dir_error(char *dir);
int		args_error(char *fn);
int		export_key_error(char *key);
int		quotes_error(void);
int		ft_count_args(char **argv);

#endif
