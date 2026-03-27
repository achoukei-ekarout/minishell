/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:32:44 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/26 21:03:13 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_ast	*abstract_syntax_tree;
	t_gc	*garbage_collector;
	t_gc	*p_garbage_collector;
	t_vars	vars;

	signal(SIGINT, sigint_handler);
    rl_catch_signals = 0;
	p_garbage_collector = NULL;
	vars_init(&vars, envp);
	if (!argc || !argv)
		return (0);
	while (1)
	{
		garbage_collector = NULL;
		tokens = NULL;
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (!*input)
			continue ;
		tokens = tokenize(input, &garbage_collector);
		if (!tokens)
		{
			free_garbage(&garbage_collector);
			free(input);
			continue ;
		}
		param_expand(&tokens, vars, &garbage_collector);
			// Here will be the expansion of the tokens one by one
		// print_tokens(tokens);
		abstract_syntax_tree = parse(tokens, &garbage_collector);
		// print_tree(abstract_syntax_tree);
		execute_ast(abstract_syntax_tree, &vars, &garbage_collector);
		free_garbage(&garbage_collector);
		free(input);
	}
	free_garbage(&p_garbage_collector);
	env_clear(vars.env);
	env_clear(vars.exp);
	rl_clear_history();
	return (0);
}
