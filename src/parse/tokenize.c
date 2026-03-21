/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 04:04:53 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/21 10:27:06 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_word(char *line, int *i)
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
		}
		(*i)++;
	}
	len = *i - start;
	word = malloc(len + 1);
	ft_strlcpy(word, line + start, len + 1);
	word[len] = '\0';
	return (word);
}

t_token	*read_operator(char *line, int *i)
{
	if (line[*i] == '|')
	{
		(*i)++;
		return (create_token(TOKEN_PIPE, ft_strdup("|")));
	}
	if (line[*i] == '<')
	{
		(*i)++;
		if (line[*i] == '<')
			return ((*i)++, create_token(TOKEN_HEREDOC, ft_strdup("<<")));
		else
			return (create_token(TOKEN_REDIR_IN, ft_strdup("<")));
	}
	if (line[*i] == '>')
	{
		(*i)++;
		if (line[*i] == '>')
			return ((*i)++, create_token(TOKEN_REDIR_APPEND, ft_strdup(">>")));
		else
			return (create_token(TOKEN_REDIR_OUT, ft_strdup(">")));
	}
	return (NULL);
}

t_token	*tokenize(char *line)
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
			token = create_token(0, ft_substr(line, start, (i - start) + 1));
		}
		else if (is_operator(line[i]))
		token = read_operator(line, &i);
		else if (line[i])
		token = create_token(TOKEN_WORD, read_word(line, &i));
		if (token)
			add_token(&t_tokens, token);
	}
	return (t_tokens);
}
