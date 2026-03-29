/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:32:44 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/29 23:01:24 by ekarout          ###   ########.fr       */
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

void	read_input(char	*input, t_vars *vars, t_gc **gc, t_gc **perm_gc)
{
	t_token	*tokens;
	t_ast	*abstract_syntax_tree;

	tokens = NULL;
	tokens = tokenize(input, gc);
	if (!tokens)
		return ;
	param_expand(&tokens, *vars, gc);
	// print_tokens(tokens);
	abstract_syntax_tree = parse(tokens, gc);
	proccess_heredoc(abstract_syntax_tree);
	// print_tree(abstract_syntax_tree);
	execute_ast(abstract_syntax_tree, vars, gc, perm_gc);
}

void	run_shell(t_vars *vars, t_gc **perm_gc)
{
	char	*input;
	t_gc	*gc;

	while (1)
	{
		gc = NULL;
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (!*input)
			continue ;
		read_input(input, vars, &gc, perm_gc);
		free_garbage(&gc);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_gc	*perm_gc;
	t_vars	vars;

	if (!argc || !argv)
		return (0);
	signal(SIGINT, sigint_handler);
	rl_catch_signals = 0;
	perm_gc = NULL;
	vars_init(&vars, envp, &perm_gc);
	run_shell(&vars, &perm_gc);
	free_garbage(&perm_gc);
	// env_clear(vars.env);
	// env_clear(vars.exp);
	rl_clear_history();
	return (0);
}
