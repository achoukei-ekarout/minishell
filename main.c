/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:32:44 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/04 21:42:02 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0;

void sigint_prompt(int sig)
{
	(void)sig;
	g_signal = SIGINT;

	write(1, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void sigint_exec(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

void setup_signals_prompt(void)
{
    signal(SIGINT, sigint_prompt);
    signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_exec(void)
{
    signal(SIGINT, sigint_exec);
    signal(SIGQUIT, SIG_IGN);
}

void	read_input(char	*input, t_vars *vars, t_gc **gc, t_gc **perm_gc)
{
	t_token	*tokens;
	t_ast	*abstract_syntax_tree;

	tokens = NULL;
	if (!valid_redir(input, vars))
		return ;
	tokens = tokenize(input, gc, vars);
	if (!tokens)
	{
		vars->exit_code = 2;
		return ;
	}
	check_heredoc(&tokens);
	param_expand(&tokens, *vars, gc);
	if (!tokens)
	{
		vars->exit_code = 2;
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
			vars->exit_code = 130;
		vars->line_counter ++;
		if (!input)
			input = "exit";
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
