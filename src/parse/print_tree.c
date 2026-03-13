/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:08:00 by user              #+#    #+#             */
/*   Updated: 2026/03/13 17:15:06 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_ast *node)
{
	if (!node)
		return ;
	printf("%d\n", node->type);
	print_tree(node->left);
	print_tree(node->right);
}
