/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 23:09:08 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/17 09:13:08 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_redir **redir)
{
	t_redir	*current;
	t_redir	*next;

	current = *redir;
	while (current)
	{
		next = current->next;
		free(current->file);
		current->file = NULL;
		free(current);
		current = next;
	}
}

void	free_ast_tree(t_ast **ast)
{
	free_ast_node(*ast);
}

void	free_ast_node(t_ast *node)
{
	if (!node)
		return ;
	free_arr(&(node->argv));
	free_redir(&(node->redir));
	free_ast_node(node->left);
	free_ast_node(node->right);
	free(node);
}
