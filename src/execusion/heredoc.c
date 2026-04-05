/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 08:43:13 by achoukei          #+#    #+#             */
/*   Updated: 2026/04/06 02:49:58 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	proccess_heredoc(t_ast *node, t_vars *vars, t_gc **head_gc)
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

void	proccess_node_heredoc(t_ast *node, t_vars *vars, t_gc **head_gc)
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

int	apply_heredoc(char *delimeter, t_token_type type,
		t_vars *vars, t_gc **head_gc)
{
	char	*line;
	char	*expand;
	int		fd[2];
	int		eof_start;

	if (pipe(fd) == -1)
		perror("pipe");
	eof_start = vars->line_counter;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			heredoc_error(eof_start, *vars);
			break;
		}
		if (ft_strcmp(line, delimeter) == 0)
			break ;
		if (type == TOKEN_HEREDOC)
		{
			expand = expand_value(line, *vars, head_gc);
			write(fd[1], expand, ft_strlen(expand));
		}
		else
			write(fd[1], line, ft_strlen(line));
		vars->line_counter++;
		write(fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}

int	check_expand(t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'' || token->value[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

void	check_heredoc(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC && current->next)
		{
			if (check_expand(current->next))
				current->type = TOKEN_HEREDOC_NOEXP;
			else
				current->type = TOKEN_HEREDOC;
		}
		current = current->next;
	}
}
