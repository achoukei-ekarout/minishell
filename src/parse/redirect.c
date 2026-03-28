/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 23:11:06 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/27 21:15:47 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT || type == TOKEN_HEREDOC);
}

void	handle_redirection(t_ast *node, t_token **tokens, t_gc **head_gc)
{
	t_redir	*redirect;
	t_redir	*last;

	redirect = allocate(head_gc, sizeof(t_redir));
	redirect->next = NULL;
	redirect->fd = -1;
	redirect->type = (*tokens)->type;
	(*tokens) = (*tokens)->next;
	redirect->file = ft_strdup_allocate((*tokens)->value, head_gc);
	if (!node->redir)
	{
		node->redir = redirect;
		return ;
	}
	last = node->redir;
	while (last->next)
		last = last->next;
	last->next = redirect;
}
