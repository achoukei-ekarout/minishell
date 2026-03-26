/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:00:54 by user              #+#    #+#             */
/*   Updated: 2026/03/26 14:05:03 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse(t_token *tokens, t_gc **head_gc)
{
	return (parse_pipeline(&tokens, head_gc));
}

t_ast	*parse_pipeline(t_token **tokens, t_gc **head_gc)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_command(tokens, head_gc);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		node = create_pipe_node(head_gc);
		node->left = left;
		node->right = parse_command(tokens, head_gc);
		left = node;
	}
	return (left);
}

t_ast	*parse_command(t_token **tokens, t_gc **head_gc)
{
	t_ast	*node;

	node = create_command_node(head_gc);
	while ((*tokens) && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_WORD)
			add_argument(node, (*tokens)->value, head_gc);
		else if (is_redirection((*tokens)->type))
			handle_redirection(node, tokens, head_gc);
		*tokens = (*tokens)->next;
	}
	return (node);
}

void	add_argument(t_ast *node, char *value, t_gc **head_gc)
{
	node->argv = ft_join_argv(node->argv, value, head_gc);
}
