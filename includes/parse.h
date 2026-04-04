/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:53:25 by achoukei          #+#    #+#             */
/*   Updated: 2026/04/03 05:01:15 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "data.h"

char				**free_arr(char ***arr);
t_token				*tokenize(char *input, t_gc **head_gc);
int					is_operator(char c);
t_token				*create_token(t_token_type type, char *value,
						t_gc **head_gc);
void				add_token(t_token **head, t_token *node);
void				free_tokens(t_token *tokens);
int					ft_strlen_argv(char **args);
char				**ft_join_argv(char **args, char *value, t_gc **head_gc);
t_ast				*parse(t_token *tokens, t_gc **head_gc);
t_ast				*parse_pipeline(t_token **tokens, t_gc **head_gc);
t_ast				*parse_command(t_token **tokens, t_gc **head_gc);
t_ast				*create_command_node(t_gc **head_gc);
t_ast				*create_pipe_node(t_gc **head_gc);
void				add_argument(t_ast *node, char *value, t_gc **head_gc);
int					is_redirection(t_token_type type);
void				handle_redirection(t_ast *node, t_token **tokens,
						t_gc **head_gc);
void				print_tree(t_ast *node);
void				free_ast_tree(t_ast **ast);
void				free_ast_node(t_ast *node);
void				print_tokens(t_token *tokens);
int					is_quote(char c);
void				print_env(char **envp);
void				print_arr(char **arr);
int					get_quote_index(char *line, int *i);
void				skip_spaces(char *line, int *i);
int					valid_redir(char *input, t_vars *vars);
void				remove_token(t_token **head, t_token **prev, t_token *node);
void				replace_token(t_token **head, t_token **prev_node,
						t_token *new_node);

#endif