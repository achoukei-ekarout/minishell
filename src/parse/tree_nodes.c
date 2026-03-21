/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 23:12:51 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/21 10:27:09 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
