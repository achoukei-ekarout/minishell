/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:40:48 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/13 13:10:45 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ECHO | ICANON | IEXTEN | ISIG);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	write(1, "^C", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
}

void	main_signals_exit(t_vars *vars)
{
	vars->exit_code = 130;
	g_signal = 0;
	return ;
}

int	heredoc_signals_exit(int fd)
{
	close(fd);
	g_signal = SIGINT;
	restore_terminal();
	return (-1);
}
