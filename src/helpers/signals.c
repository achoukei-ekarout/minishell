/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 02:42:03 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/06 02:44:24 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_prompt(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_exec(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

void	setup_signals_prompt(void)
{
	signal(SIGINT, sigint_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_exec(void)
{
	signal(SIGINT, sigint_exec);
	signal(SIGQUIT, SIG_IGN);
}
