/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:00:54 by user              #+#    #+#             */
/*   Updated: 2026/03/13 15:31:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_argv(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	*allocate(char *arg)
{
	char	*new_arg;
	int		len;

	len = ft_strlen(arg);
	new_arg = malloc(len + 1);
	if (!new_arg)
		return (NULL);
	return (new_arg);
}

char	**ft_join_argv(char **args, char *value)
{
	int		args_len;
	char	**new_args;
	int		i;

	i = 0;
	args_len = ft_strlen_argv(args);
	new_args = malloc(sizeof(char *) * (args_len + 1));
	while (args[i])
	{
		new_args = allocate(args[i]);
		ft_memmove(new_args[i], args[i], ft_strlen(args[i]));
		i++;
	}
	ft_memmove(new_args[i], value, ft_strlen(value));
	new_args[++i] = NULL;
	return (new_args);
}

t_ast	*parse(t_token *tokens)
{
	return (parse_pipeline(&tokens));
}

t_ast	*pasre_pipeline(t_token **tokens)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_command(tokens);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		node = create_pipe_node();
		node->left = left;
		node->right = parse_command(tokens);
		left = node;
	}
	return (left);
}

t_ast	*parse_command(t_token **tokens)
{
	t_ast	*node;

	node = create_command_node();
	while ((*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_WORD)
			add_argument(node, (*tokens)->value);
		else if (is_redirection((*tokens)->type))
			handle_redirection(node, tokens);
		*tokens = (*tokens)->next;
	}
	return (node);
}

t_ast	*create_command_node(void)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	node->type = NODE_COMMAND;
	node->argv = NULL;
	node->redir = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast	*create_pipe_node(void)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	node->type = NODE_PIPE;
	node->left = NULL;
	node->right = NULL;
	node->argv = NULL;
	node->redir = NULL;
	return (node);
}

void	add_argument(t_ast *node, char *value)
{
	int	argv_len;

	argv_len = ft_strlen_argv(node->argv);
	node->argv = ft_join_argv(node->argv, value);
}

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT || type == TOKEN_HEREDOC);
}

void	handle_redirection(t_ast *node, t_token **tokens)
{
	t_redir	*redirect;

	redirect = malloc(sizeof(t_redir));
	redirect->next = NULL;
	redirect->type = (*tokens)->type;
	(*tokens) = (*tokens)->next;
	redirect->file = (*tokens)->value;
	while (node->redir)
		node->redir = node->redir->next;
	node->redir = redirect;
}
