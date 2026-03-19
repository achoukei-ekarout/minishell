/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:39:34 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/19 23:19:57 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*expand_value(char *value, t_env **env)
// {
// 	char	*param;
// 	char	*param_value;
// 	int		i;
// 	int		start;
// 	char	stop;

// 	i = 0;
// 	stop = ' ';
// 	while(value[i])
// 	{
// 		if (value[i] == '$')
// 		{
// 			if(value[i] == '{')
// 			{
// 				stop = '}';
// 				i++;
// 			}
// 			start = i;
// 			while (value[i] != stop)
// 				i++;
// 			param = ft_substr(value, start, i - start);
// 			param_value = get_env_value(env, param)
// 		}
// 	}
// }

char	*get_value(char *value, int *i, t_env **env)
{
	int		start;
	char	*key;
	char	*result;

	if (value[*i] == '{')
		(*i)++;
	start = *i;
	while ((ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	if(value[*i] == '}')
		(*i)++;
	key = ft_substr(value, start, *i - start);
	result = get_env_value(env, key);
	free(key);
	return (result);
}

int	get_value_len(char *value, int *i, t_env **env)
{
	int		start;
	char	*key;
	char	*result;

	if (value[*i] == '{')
		(*i)++;
	start = *i;
	while ((ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	if(value[*i] == '}')
		(*i)++;
	key = ft_substr(value, start, *i - start);
	result = get_env_value(env, key);
	free(key);
	if (!result)
		return (0);
	return (ft_strlen(result));
}

int	get_new_size(char *value, t_env **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (value[i])
	{
		if (value[i] == '\'')
		{
			i++;
			while (value[i] != '\'' && value[i])
			{
				i++;
				len++;
			}
			if(value[i] == '\'')
				i++;
		}
		else if (value[i] == '\"')
		{
			i++;
			while (value[i] != '\"' && value[i])
			{
				if(value[i] == '$')
				{
					i++;
					len += get_value_len(value, &i, env);
				}
				else
				{
					i++;
					len++;
				}
			}
			if(value[i] == '\"')
				i++;
		}
		else if (value[i] == '$')
		{
			i++;
			len += get_value_len(value, &i, env);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*expand_value(char *value, t_env **env)
{
	char	*new_value;
	char	*expanded;
	int		i;
	int		j;
	int		k;

	i = get_new_size(value, env);
	new_value = (char *)malloc(sizeof(char) * (i + 1));
	new_value[i] = 0;
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '\'')
		{
			i++;
			while (value[i] != '\'' && value[i])
			{
				new_value[j] = value[i];
				i++;
				j++;
			}
			if (value[i] == '\'')
				i++;
		}
		else if (value[i] == '\"')
		{
			i++;
			while (value[i] != '\"' && value[i])
			{
				if(value[i] == '$')
				{
					i++;
					expanded = get_value(value, &i, env);
					if(expanded)
					{
						k = 0;
						while (expanded[k])
						{
							new_value[j] = expanded[k];
							j++;
							k++;
						}
					}
				}
				else
				{
					new_value[j] = value[i];
					i++;
					j++;
				}
			}
			if(value[i] == '\"')
				i++;
		}
		else if (value[i] == '$')
		{
			i++;
			expanded = get_value(value, &i, env);
			if (expanded)
			{
				k = 0;
				while (expanded[k])
				{
					new_value[j] = expanded[k];
					j++;
					k++;
				}
			}
		}
		else
		{
			new_value[j] = value[i];
			i++;
			j++;
		}
	}
	return (new_value);
}

// void	expand(t_token **token, t_env **env)
// {
// 	char	*value;
// 	char	*new_value;

// 	value = (*token)->value;
// 	expand_value(value, env);
// 	free((*token)->value);
// 	(*token)->value = new_value;
// }

// void	param_expand(t_token **tokens, t_env **env)
// {
// 	t_token	*curr;

// 	curr = *tokens;
// 	while (curr)
// 	{
// 		expand(&curr, env);
// 		curr = curr->next;
// 	}
// }

