/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:59:01 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/13 13:02:17 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRAS_H
# define EXTRAS_H

# include "minishell.h"

void	run_shell_gnl(t_vars *vars, t_gc **perm_gc);
int		heredoc_gnl(char *delimeter, int fd_out, t_vars *vars);
int		heredoc_gnl_expand(char *delimeter, int fd_out,
			t_vars *vars, t_gc **head_gc);
void	print_tree(t_ast *node);
void	print_tokens(t_token *tokens);
void	print_env(char **envp);
void	print_arr(char **arr);
void	free_redir(t_redir **redir);
void	free_ast_tree(t_ast **ast);
void	free_ast_node(t_ast *node);
void	env_clear(t_env **env);
void	free_tokens(t_token *tokens);

#endif