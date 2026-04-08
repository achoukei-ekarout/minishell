/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:28:46 by user              #+#    #+#             */
/*   Updated: 2026/04/08 13:37:58 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "parse.h"

void	execute_ast(t_ast *node, t_vars *vars, t_gc **head_gc, t_gc **perm_gc);
void	execute_pipe(t_ast *node, t_vars *vars, t_garbage garbage);
void	execute_command(t_ast *node, t_vars *vars, t_garbage garbage);
int		apply_redirections(t_redir *redir, t_vars *vars);
char	*get_path(char **envp);
char	*get_path(char **envp);
char	*get_path_name(char *func_name, char **paths);
char	**get_all_paths(char **envp, t_gc **head_gc);
int		is_built_ins(char *str);
int		call_built_ins(char **input, t_vars *vars, t_garbage garbage);
void	child_process(t_ast *node, t_vars *vars, t_gc **head_gc);
void	proccess_heredoc(t_ast *node, t_vars *vars, t_gc **head_gc);
void	proccess_node_heredoc(t_ast *node, t_vars *vars, t_gc **head_gc);
int		heredoc_readline_expand(char *delimeter, int fd_out,
			t_vars *vars, t_gc **head_gc);
int		heredoc_readline(char *delimeter, int fd_out, t_vars *vars);
int		check_expand(t_token *token);
void	check_heredoc(t_token **tokens);
void	handle_dir(char **argv, char **envp);
int		*open_redirections(t_redir *redir, t_vars *vars, t_gc **head_gc);
void	close_redirections(int *saved_stds);
int		apply_heredoc(char *delimeter, t_token_type type,
			t_vars *vars, t_gc **head_gc);
void	run_left_child(t_ast *node, int fd[2], t_vars *vars, t_garbage garbage);
void	run_right_child(t_ast *node, int fd[2],
			t_vars *vars, t_garbage garbage);
void	signal_exit(t_vars *vars, int status);
void	handle_built_ins(t_ast *node, t_vars *vars, t_garbage garbage);
int		handle_redir_out(t_redir *redir, t_vars *vars);
int		handle_redir_in(t_redir *redir, t_vars *vars);
void	pipe_exit(t_vars *vars, int status2);

#endif