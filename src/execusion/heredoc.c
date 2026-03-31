/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 08:43:13 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/31 00:04:20 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	proccess_heredoc(t_ast *node, t_vars vars, t_gc **head_gc)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
		proccess_node_heredoc(node, vars, head_gc);
	else if (node->type == NODE_PIPE)
	{
		proccess_heredoc(node->left, vars, head_gc);
		proccess_heredoc(node->right, vars, head_gc);
	}
}

void	proccess_node_heredoc(t_ast *node, t_vars vars, t_gc **head_gc)
{
	t_redir	*redir;

	redir = node->redir;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC || redir->type == TOKEN_HEREDOC_NOEXP)
			redir->fd = apply_heredoc(redir->file, redir->type, vars, head_gc);
		redir = redir->next;
	}
}

int	apply_heredoc(char *delimeter, t_token_type type, t_vars vars, t_gc **head_gc)
{
	int		fd[2];
	char	*line;
	char	*expand;

	if (pipe(fd) == -1)
		perror("pipe");
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimeter) == 0)
		{
			free(line);
			break ;
		}
		if (type == TOKEN_HEREDOC)
		{
			expand = expand_value(line, vars, head_gc);
			write(fd[1], expand, ft_strlen(expand));
			write(fd[1], "\n", 1);
		}
		else
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

t_token_type	check_expand(t_token *token)
{
    int i;

    i = 0;
    while (token->value[i])
    {
        if (token->value[i] == '\'' || token->value[i] == '"')
            return (TOKEN_HEREDOC_NOEXP);
		i++;
    }
    return (TOKEN_HEREDOC);
}

void	check_heredoc(t_token **tokens)
{
	t_token *current;

	current = *tokens;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC && current->next)
			current->type = check_expand(current->next);
		current = current->next;
	}
}
