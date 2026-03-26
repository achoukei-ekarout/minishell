/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:28:46 by user              #+#    #+#             */
/*   Updated: 2026/03/26 21:11:42 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "parse.h"

void	execute_ast(t_ast *node, t_vars *vars, t_gc **head_gc);
void	execute_pipe(t_ast *node, t_vars *vars, t_gc **head_gc);
void	execute_command(t_ast *node, t_vars *vars, t_gc **head_gc);
void	apply_redirections(t_redir *redir);
char	*get_path(char **envp);
char	*get_path(char **envp);
char	*get_path_name(char *func_name, char **paths);
char	**get_all_paths(char **envp, t_gc **head_gc);
int		is_built_ins(char *str);
int		call_built_ins(char *str, char **input, t_vars vars);

#endif