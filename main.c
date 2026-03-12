/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:32:44 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/12 17:44:02 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv)
{
	char	*input;
	t_token *tokens;

	if (!argc || !argv)
		return (0);
	while (1)
	{
		tokens = NULL;
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (!*input)
			continue ;
		tokens = tokenize(input);
		print_tokens(tokens);
		free_tokens(tokens);
		free(input);
	}
	return (0);
}
