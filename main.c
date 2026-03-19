/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:32:44 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/19 16:36:18 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_ast	*abstract_syntax_tree;

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
		// print_tokens(tokens);
		// expansion(&tokens); // Here will be the expansion of the tokens one by one
		abstract_syntax_tree = parse(tokens);
		// print_tree(abstract_syntax_tree);
		execute_ast(abstract_syntax_tree, envp);
		free_ast_tree(&abstract_syntax_tree);
		free_tokens(tokens);
		free(input);
	}
	rl_clear_history();
	return (0);
}
