/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:32:44 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/08 20:25:31 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	read_input(char	*input, t_vars *vars, t_gc **gc, t_gc **perm_gc)
{
	t_token	*tokens;
	t_ast	*abstract_syntax_tree;

	tokens = NULL;
	vars->input = input;
	if (!valid_redir(input, vars))
		return ;
	tokens = tokenize(input, gc, vars);
	check_heredoc(&tokens);
	param_expand(&tokens, *vars, gc);
	if (!tokens)
	{
		vars->exit_code = 0;
		return ;
	}
	// print_tokens(tokens);
	abstract_syntax_tree = parse(tokens, gc);
	proccess_heredoc(abstract_syntax_tree, vars, gc);
	// print_tree(abstract_syntax_tree);
	setup_signals_exec();
	execute_ast(abstract_syntax_tree, vars, gc, perm_gc);
	if (g_signal == SIGINT)
		vars->exit_code = 130;
}

void	run_shell(t_vars *vars, t_gc **perm_gc)
{
	char	*input;
	t_gc	*gc;

	while (1)
	{
		setup_signals_prompt();
		g_signal = 0;
		gc = NULL;
		input = readline("minishell$ ");
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			vars->exit_code = 130;
		}
		vars->line_counter ++;
		if (!input)
			input = ft_strdup("exit");
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
	rl_catch_signals = 0;
	perm_gc = NULL;
	vars_init(&vars, envp, &perm_gc, argv[0]);
	run_shell(&vars, &perm_gc);
	free_garbage(&perm_gc);
	rl_clear_history();
	return (0);
}
