/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:08:00 by user              #+#    #+#             */
/*   Updated: 2026/03/27 20:51:04 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
		printf("COMMAND\n");
	else
		printf("PIPE\n");
	print_tree(node->left);
	print_tree(node->right);
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token value: %s, Token type: %i\n", tokens->value,
			tokens->type);
		tokens = tokens->next;
	}
}

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
