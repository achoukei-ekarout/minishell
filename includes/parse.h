/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:53:25 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/11 05:48:15 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

int					ft_isspace(char c);
char				**free_arr(char ***arr);
void				execute_program(char **arr, char **envp);
t_token				*tokenize(char *input);
int					is_operator(char c);
t_token				*create_token(t_token_type type, char *value);
void				add_token(t_token **head, t_token *node);
void				print_tokens(t_token *tokens);

#endif