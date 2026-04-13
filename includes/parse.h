/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:53:25 by achoukei          #+#    #+#             */
/*   Updated: 2026/04/13 13:03:46 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "data.h"

void	read_input(char	*input, t_vars *vars, t_gc **gc, t_gc **perm_gc);
char	**free_arr(char ***arr);
t_token	*tokenize(char *input, t_gc **head_gc, t_vars *vars);
int		is_operator(char c);
t_token	*create_token(t_token_type type, char *value, t_gc **head_gc);
void	add_token(t_token **head, t_token *node);
int		ft_strlen_argv(char **args);
char	**ft_join_argv(char **args, char *value, t_gc **head_gc);
t_ast	*parse(t_token *tokens, t_gc **head_gc);
t_ast	*parse_pipeline(t_token **tokens, t_gc **head_gc);
t_ast	*parse_command(t_token **tokens, t_gc **head_gc);
t_ast	*create_command_node(t_gc **head_gc);
t_ast	*create_pipe_node(t_gc **head_gc);
void	add_argument(t_ast *node, char *value, t_gc **head_gc);
int		is_redirection(t_token_type type);
void	handle_redirection(t_ast *node, t_token **tokens, t_gc **head_gc);
int		is_quote(char c);
int		get_quote_index(char *line, int *i, t_vars *vars);
void	skip_spaces(char *line, int *i);
int		valid_redir(char *input, t_vars *vars);
void	remove_token(t_token **head, t_token **prev, t_token *node);
void	replace_token(t_token **head, t_token **prev_node, t_token *new_node);

#endif