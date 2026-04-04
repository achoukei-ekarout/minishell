/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:28:46 by user              #+#    #+#             */
/*   Updated: 2026/04/03 01:03:33 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "parse.h"

void	execute_ast(t_ast *node, t_vars *vars, t_gc **head_gc, t_gc **perm_gc);
void	execute_pipe(t_ast *node, t_vars *vars, t_gc **head_gc, t_gc **perm_gc);
void	execute_command(t_ast *node, t_vars *vars, t_gc **gc, t_gc **perm_gc);
int		apply_redirections(t_redir *redir);
char	*get_path(char **envp);
char	*get_path(char **envp);
char	*get_path_name(char *func_name, char **paths);
char	**get_all_paths(char **envp, t_gc **head_gc);
int		is_built_ins(char *str);
int		call_built_ins(char **input, t_vars *vars, t_gc **gc, t_gc **perm_gc);
void	child_process(t_ast *node, t_vars *vars, t_gc **head_gc);
void	proccess_heredoc(t_ast *node, t_vars vars, t_gc **head_gc);
void	proccess_node_heredoc(t_ast *node, t_vars vars, t_gc **head_gc);
int		check_expand(t_token *token);
void	check_heredoc(t_token **tokens);
void	handle_dir(char **argv, char **envp);
int		apply_heredoc(char *delimeter, t_token_type type,
			t_vars vars, t_gc **head_gc);

#endif