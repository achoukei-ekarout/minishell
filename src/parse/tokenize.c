/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 04:04:53 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/28 15:32:55 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_word(char *line, int *i, t_gc **head_gc)
{
	int		start;
	int		len;
	char	*word;
	int		quote_index;

	quote_index = 0;
	start = *i;
	while (line[*i] && line[*i] != ' ' && !is_operator(line[*i]))
	{
		if (is_quote(line[(*i)]))
		{
			quote_index = (*i);
			while (line[*i] != line[quote_index])
				(*i)++;
			// if (!line[*i])
			// {
			// 	quotes_error();
			// 	return (NULL);
			// }
		}
		(*i)++;
	}
	len = *i - start;
	word = allocate(head_gc, len + 1);
	ft_strlcpy(word, line + start, len + 1);
	word[len] = '\0';
	return (word);
}

t_token	*check_redir_type(t_token_type type, t_gc **head_gc, int *i)
{
	if (type == TOKEN_HEREDOC)
		return ((*i)++, create_token(TOKEN_HEREDOC, ft_strdup_allocate("<<",
					head_gc), head_gc));
	if (type == TOKEN_REDIR_IN)
		return (create_token(TOKEN_REDIR_IN, ft_strdup_allocate("<",
					head_gc), head_gc));
	if (type == TOKEN_REDIR_APPEND)
		return ((*i)++, create_token(TOKEN_REDIR_APPEND,
				ft_strdup_allocate(">>", head_gc), head_gc));
	if (type == TOKEN_REDIR_OUT)
		return (create_token(TOKEN_REDIR_OUT, ft_strdup_allocate(">",
					head_gc), head_gc));
	return (NULL);
}

t_token	*read_operator(char *line, int *i, t_gc **head_gc)
{
	if (line[*i] == '|')
	{
		(*i)++;
		return (create_token(TOKEN_PIPE, ft_strdup_allocate("|", head_gc),
				head_gc));
	}
	if (line[*i] == '<')
	{
		(*i)++;
		if (line[*i] == '<')
			return (check_redir_type(TOKEN_HEREDOC, head_gc, i));
		else
			return (check_redir_type(TOKEN_REDIR_IN, head_gc, i));
	}
	if (line[*i] == '>')
	{
		(*i)++;
		if (line[*i] == '>')
			return (check_redir_type(TOKEN_REDIR_APPEND, head_gc, i));
		else
			return (check_redir_type(TOKEN_REDIR_OUT, head_gc, i));
	}
	return (NULL);
}

t_token	*tokenize(char *line, t_gc **head_gc)
{
	int		i;
	t_token	*t_tokens;
	t_token	*token;
	int		start;

	t_tokens = NULL;
	i = 0;
	while (line[i])
	{
		token = NULL;
		while (ft_isspace(line[i]))
			i++;
		if (is_quote(line[i]))
		{
			start = get_quote_index(line, &i);
			token = create_token(0, ft_substr_allocate(line, start, (i - start)
						+ 1, head_gc), head_gc);
		}
		else if (is_operator(line[i]))
			token = read_operator(line, &i, head_gc);
		else if (line[i])
			token = create_token(TOKEN_WORD, read_word(line, &i, head_gc),
					head_gc);
		if (token)
			add_token(&t_tokens, token);
	}
	return (t_tokens);
}
