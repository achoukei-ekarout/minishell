/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:28:46 by user              #+#    #+#             */
/*   Updated: 2026/03/24 15:33:53 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "parse.h"

void	execute_ast(t_ast *node, char **envp, t_gc **head_gc);
void	execute_pipe(t_ast *node, char **envp, t_gc **head_gc);
void	execute_command(t_ast *node, char **envp, char **paths);
void	apply_redirections(t_redir *redir);
char	*get_path(char **envp);
char	*get_path(char **envp);
char	*get_path_name(char *func_name, char **paths);
char	**get_all_paths(char **envp, t_gc **head_gc);
int		is_built_ins(char *str);

#endif