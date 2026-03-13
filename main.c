/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:32:44 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/13 13:45:17 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv)
{
	char	*input;
	t_token *tokens;
	t_ast *abstract_syntax_tree;

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
		abstract_syntax_tree = parse(tokens);

		// execute_ast(ast);

		free_ast(abstract_syntax_tree);
		free_tokens(tokens);
		free(input);
	}
	return (0);
}
