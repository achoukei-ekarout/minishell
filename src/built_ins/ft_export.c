/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:16:24 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/08 00:57:01 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_export_key_value(char *arg)
// {
// 	t_env	*env;
// 	t_env	*temp;
// 	char	*key;

// 	env = g_shell.env;
	
// 	temp = create_env_node(arg);
// 	if (!temp)
// 		return ;
	
// 	// if(is_key(key_value[0]))
// 	// {
// 	// 	if(key_value[1])
// 	// 	{
// 	// 		temp = find_key(key_value[0]);
// 	// 		if (temp)
// 	// 		{
// 	// 			temp->value = key_value[1];
// 	// 			free(key_value[0]);
// 	// 			free(key_value[1]);
// 	// 			free(key_value);
// 	// 			return ;
// 	// 		}
// 	// 		temp = create_env_node(arg);
// 	// 		free(key_value[0]);
// 	// 		free(key_value[1]);
// 	// 		free(key_value);
// 	// 	}
// 	// }
// }

// void	ft_export(char *arg)
// {
// 	t_env	*env;

// 	env = g_shell.env;
// 	if(!arg)
// 		return ;
// 	if (ft_strchr(arg, '='))
// 	{
// 		ft_export_key_value(arg);
// 	}
// }
