/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 19:18:59 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/23 16:24:28 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "data.h"

typedef struct s_expand
{
	char		*old_value;
	char		*new_value;
	t_env		**env;
}	t_expand;

void		param_expand(t_token **tokens, t_env **env);
void		expand(t_token **token, t_env **env);
char		*expand_value(char *value, t_env **env);
t_expand	*init_expand_data(char *value, t_env **env, int len);
void		handle_double_quotes(t_expand *expand_data, int *i, int *j);
void		handle_dollar(t_expand *expand_data, int *i, int *j);
void		handle_single_quotes(t_expand *expand_data, int *i, int *j);
int			get_new_size(char *value, t_env **env);
void		handle_double_quote_len(char *value, int *i, int *len, t_env **env);
void		handle_single_quotes_len(char *value, int *i, int *len);
int			get_value_len(char *value, int *i, t_env **env);
char		*get_value(char *value, int *i, t_env **env);

#endif