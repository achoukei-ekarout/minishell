/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 02:42:41 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/13 13:11:22 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

extern int	g_signal;

void	sigint_prompt(int sig);
void	sigint_exec(int sig);
void	setup_signals_prompt(void);
void	setup_signals_exec(void);
void	setup_signals_heredoc(void);
void	restore_terminal(void);
void	main_signals_exit(t_vars *vars);
int		heredoc_signals_exit(int fd);

#endif
