/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:32:44 by ekarout           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/03/28 14:45:37 by achoukei         ###   ########.fr       */
=======
/*   Updated: 2026/03/27 21:33:44 by ekarout          ###   ########.fr       */
>>>>>>> collab
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

void	read_input(char	*input, t_vars *vars, t_gc **garbage_collector)
{
	t_token	*tokens;
	t_ast	*abstract_syntax_tree;

	tokens = NULL;
	tokens = tokenize(input, garbage_collector);
	if (!tokens)
		return ;
	param_expand(&tokens, *vars, garbage_collector);
	// print_tokens(tokens);
	abstract_syntax_tree = parse(tokens, garbage_collector);
	// print_tree(abstract_syntax_tree);
	execute_ast(abstract_syntax_tree, vars, garbage_collector);
}

void	run_shell(t_vars *vars)
{
	char	*input;
	t_gc	*garbage_collector;

	while (1)
	{
		garbage_collector = NULL;
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (!*input)
			continue ;
		read_input(input, vars, &garbage_collector);
		free_garbage(&garbage_collector);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_gc	*p_garbage_collector;
	t_vars	vars;

	if (!argc || !argv)
		return (0);
	signal(SIGINT, sigint_handler);
	rl_catch_signals = 0;
	p_garbage_collector = NULL;
	vars_init(&vars, envp);
	run_shell(&vars);
	free_garbage(&p_garbage_collector);
	env_clear(vars.env);
	env_clear(vars.exp);
	rl_clear_history();
	return (0);
}
