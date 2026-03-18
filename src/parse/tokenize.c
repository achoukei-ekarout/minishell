/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 04:04:53 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/13 02:08:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_word(char *line, int *i/* , t_env *env */)
{
	t_quote	state = NO_QUOTE;
	char	*result = ft_strdup("");
	char	*tmp;

	while (line[*i])
	{
		if (state == NO_QUOTE && (ft_isspace(line[*i]) || is_operator(line[*i])))
			break;
		if (line[*i] == '\'' && state == NO_QUOTE)
			state = SINGLE_QUOTE;
		else if (line[*i] == '\'' && state == SINGLE_QUOTE)
			state = NO_QUOTE;
		else if (line[*i] == '"' && state == NO_QUOTE)
			state = DOUBLE_QUOTE;
		else if (line[*i] == '"' && state == DOUBLE_QUOTE)
			state = NO_QUOTE;
		else if (line[*i] == '$' && state != SINGLE_QUOTE)
		{
			tmp = "test";/* expand_variable(line, i, env); */
			result = str_join_free(result, tmp);
			continue;
		}
		else
		{
			tmp = ft_substr(line, *i, 1);
			result = str_join_free(result, tmp);
		}
		(*i)++;
	}
	if (state != NO_QUOTE)
	{
		printf("minishell: unclosed quote\n");
		free(result);
		return (NULL);
	}
	return (result);
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
	t_token	*token;

	tokens = NULL;
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

// void	print_tokens(t_token *tokens)
// {
// 	while (tokens)
// 	{
// 		if (tokens->value)
// 			printf("TYPE: %d VALUE: %s\n", tokens->type, tokens->value);
// 		else
// 			printf("TYPE: %d VALUE: NULL\n", tokens->type);
// 		tokens = tokens->next;
// 	}
// }
