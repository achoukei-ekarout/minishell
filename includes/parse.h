/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:53:25 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/13 17:36:17 by user             ###   ########.fr       */
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

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE
}					t_node_type;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_ast
{
	t_node_type		type;

	char			**argv;
	t_redir			*redir;

	struct s_ast	*left;
	struct s_ast	*right;

}					t_ast;

typedef enum e_quote
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote;

int					ft_isspace(char c);
char				**free_arr(char ***arr);
t_token				*tokenize(char *input);
int					is_operator(char c);
t_token				*create_token(t_token_type type, char *value);
void				add_token(t_token **head, t_token *node);
void				free_tokens(t_token *tokens);
int					ft_strlen_argv(char **args);
char				**ft_join_argv(char **args, char *value);
t_ast				*parse(t_token *tokens);
t_ast				*parse_pipeline(t_token **tokens);
t_ast				*parse_command(t_token **tokens);
t_ast				*create_command_node(void);
t_ast				*create_pipe_node(void);
void				add_argument(t_ast *node, char *value);
int					is_redirection(t_token_type type);
void				handle_redirection(t_ast *node, t_token **tokens);
void				print_tree(t_ast *node);
void				free_ast_tree(t_ast **ast);
void				free_ast_node(t_ast *node);
void				print_tokens(t_token *tokens);
int					is_quote(char c);

#endif