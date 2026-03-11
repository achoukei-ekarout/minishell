/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 04:04:53 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/11 05:56:07 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_word(char *line, int *i)
{
	int		start;
	int		len;
	char	*word;

	start = *i;
	while (line[*i] && line[*i] != ' ' && !is_operator(line[*i]))
		(*i)++;
	len = *i - start;
	word = malloc(len + 1);
	ft_strlcpy(word, line + start, len);
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
		{
			(*i)++;
			return (create_token(TOKEN_HEREDOC, ft_strdup("<<")));
		}
		else
		{
			(*i)++;
			return (create_token(TOKEN_REDIR_IN, ft_strdup("<")));
		}
	}
	if (line[*i] == '>')
	{
		(*i)++;
		if (line[*i] == '>')
		{
			(*i)++;
			return (create_token(TOKEN_REDIR_APPEND, ft_strdup(">>")));
		}
		else
		{
			(*i)++;
			return (create_token(TOKEN_REDIR_OUT, ft_strdup(">")));
		}
	}
	return (NULL);
}

t_token	*tokenize(char *line)
{
	int		i;
	t_token	*tokens;
	char	*word;
	t_token *token;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		if (is_operator(line[i]))
		{
			token = read_operator(line, &i);
			if (token)
				add_token(&tokens, token);
		}
		else
		{
			word = read_word(line, &i);
			add_token(&tokens, create_token(TOKEN_WORD, word));
		}
	}
	return (tokens);
}

void print_tokens(t_token *tokens)
{
    while (tokens)
    {
        if (tokens->value)
            printf("TYPE: %d VALUE: %s\n", tokens->type, tokens->value);
        else
            printf("TYPE: %d VALUE: NULL\n", tokens->type);

        tokens = tokens->next;
    }
}
