/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:09:30 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/07 15:53:43 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_double_quotes(t_expand *expand_data, int *i, int *j, t_gc **head_gc)
{
	(*i)++;
	while (expand_data->old_value[*i] != '\"' && expand_data->old_value[*i])
	{
		if (expand_data->old_value[*i] == '$')
			handle_dollar(expand_data, i, j, head_gc);
		else
		{
			expand_data->new_value[*j] = expand_data->old_value[*i];
			(*i)++;
			(*j)++;
		}
	}
	if (expand_data->old_value[*i] == '\"')
		(*i)++;
}

void	handle_single_quotes(t_expand *expand_data, int *i, int *j)
{
	(*i)++;
	while (expand_data->old_value[*i] != '\'' && expand_data->old_value[*i])
	{
		expand_data->new_value[*j] = expand_data->old_value[*i];
		(*i)++;
		(*j)++;
	}
	if (expand_data->old_value[*i] == '\'')
		(*i)++;
}
