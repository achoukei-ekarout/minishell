/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 23:11:06 by achoukei          #+#    #+#             */
/*   Updated: 2026/04/06 08:27:57 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT || type == TOKEN_HEREDOC
		|| type == TOKEN_HEREDOC_NOEXP);
}

int	skip_quotes(char *s, int *i)
{
	if (s[*i] == '\'')
		{
			(*i)++;
			while (s[*i] && s[*i] != '\'')
				(*i)++;
			if (!s[*i])
				return (2);
			return (1);
		}
	if (s[*i] == '\"')
	{
		(*i)++;
		while (s[*i] && s[*i] != '\"')
			(*i)++;
		if (!s[*i])
			return (2);
		return (1);
	}
	return (0);
}

int	valid_redir(char *input, t_vars *vars)
{
	char	*s;
	int		i;
	int		quotes;

	s = ft_strtrim(input, " \n\t\v\f\r");
	i = -1;
	if (s[0] == '|')
	{
		vars->exit_code = redir_error('|', *vars);
		free(s);
		return (0);
	}
	while (s[++i])
	{
		quotes = skip_quotes(s, &i);
		if (quotes == 1)
			continue ;
		if (quotes == 2)
			break ;
		if (s[i] == '|')
		{
			i++;
			while (s[i] && ft_isspace(s[i]))
				i++;
			if (!s[i] || s[i] == '|')
			{
				vars->exit_code = redir_error(s[i], *vars);
				free(s);
				return (0);
			}
		}
		if (s[i] == '>' || s[i] == '<')
		{
			i++;
			if (s[i] == '>' || s[i] == '<')
				i++;
			while (s[i] && ft_isspace(s[i]))
				i++;
			if (!s[i] || is_operator(s[i]))
			{
				vars->exit_code = redir_error(s[i], *vars);
				free(s);
				return (0);
			}
		}
	}
	free(s);
	return (1);
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
