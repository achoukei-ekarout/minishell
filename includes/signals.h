/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 02:42:41 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/06 02:47:46 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

extern int	g_signal;

void	sigint_prompt(int sig);
void	sigint_exec(int sig);
void	setup_signals_prompt(void);
void	setup_signals_exec(void);

#endif
