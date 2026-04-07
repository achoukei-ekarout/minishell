/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 19:18:59 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/07 10:09:03 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "data.h"
# include "garbage_collector.h"

typedef struct s_expand
{
	char		*old_value;
	char		*new_value;
	t_vars		vars;
}	t_expand;

void		param_expand(t_token **tokens, t_vars vars, t_gc **head_gc);
t_token		*expand(t_token **token, t_vars vars, t_gc **head_gc);
char		*expand_value(char *value, t_vars vars, t_gc **head_gc);
t_expand	*init_expand_data(char *value, t_vars vars,
				int len, t_gc **head_gc);
void		handle_double_quotes(t_expand *expand_data, int *i, int *j);
void		handle_character(t_expand *expand_data, int *i, int *j);
void		handle_dollar(t_expand *expand_data, int *i, int *j);
void		handle_tilde(t_expand *expand_data, int *i, int *j);
void		handle_single_quotes(t_expand *expand_data, int *i, int *j);
int			get_new_size(char *value, t_vars vars);
void		handle_double_quote_len(char *value, int *i, int *len, t_vars vars);
void		handle_single_quotes_len(char *value, int *i, int *len);
int			get_value_len(char *value, int *i, t_vars vars);
char		*get_value(char *value, int *i, t_vars vars);
int			check_for_new_token(char *value);
t_token		*expanded_token(char *value, t_vars vars, t_gc **head_gc);
t_token		*start_node(char *new_value, char **split, t_gc **head_gc);

#endif