/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:13:50 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/15 13:48:56 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_pipe(char *s, int *i, t_vars *vars)
{
	(*i)++;
	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
	if (!s[*i] || s[*i] == '|')
	{
		vars->exit_code = redir_error(s[*i], *vars);
		return (0);
	}
	return (1);
}

int	check_redir(char *s, int *i, t_vars *vars)
{
	int redir;

	redir = *i;
	(*i)++;
	if (s[*i] == s[redir])
		(*i)++;
	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
	if (!s[*i] || is_operator(s[*i]))
	{
		vars->exit_code = redir_error(s[*i], *vars);
		return (0);
	}
	return (1);
}

int	check_tokens(char *s, t_vars *vars)
{
	int	i;
	int	quotes;

	i = -1;
	while (s[++i])
	{
		quotes = skip_quotes(s, &i);
		if (quotes == 1)
			continue ;
		if (quotes == 2)
			break ;
		if (s[i] == '|' && !check_pipe(s, &i, vars))
			return (0);
		if ((s[i] == '>' || s[i] == '<') && !check_redir(s, &i, vars))
			return (0);
	}
	return (1);
}

int	valid_redir(char *input, t_vars *vars)
{
	char	*s;
	int		result;

	s = ft_strtrim(input, " \n\t\v\f\r");
	if (s[0] == '|')
	{
		vars->exit_code = redir_error('|', *vars);
		free(s);
		return (0);
	}
	result = check_tokens(s, vars);
	free(s);
	return (result);
}
