/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:06:31 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/07 08:55:20 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE
}					t_node_type;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_HEREDOC_NOEXP
}	t_token_type;

typedef enum e_quote
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}					t_quote;

typedef struct s_env_data
{
	char			*key;
	char			*value;
}	t_env_data;

typedef struct s_env
{
	t_env_data		*data;
	struct s_env	*next;
}	t_env;

typedef struct s_vars
{
	t_env	**env;
	t_env	**exp;
	int		exit_code;
	int		line_counter;
	char	*executer_name;
	char	*input;
}	t_vars;

typedef struct e_gc
{
	void		*value;
	struct e_gc	*next;
}				t_gc;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				fd;
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

typedef struct s_garbage
{
	t_gc	**temp_gc;
	t_gc	**perm_gc;
}	t_garbage;

#endif
