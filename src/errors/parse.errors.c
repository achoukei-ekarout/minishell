/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:29:16 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/04 18:17:07 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_error(t_vars vars)
{
	ft_putchar_fd('-', 2);
	ft_putstr_fd(vars.executer_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("error: unclosed quote\n", 2);
	return (2);
}

int	redir_error(char s, t_vars vars)
{
	ft_putchar_fd('-', 2);
	ft_putstr_fd(vars.executer_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	if (s)
		ft_putchar_fd(s, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("\'\n", 2);
	return (2);
}

int file_error(char *file, t_vars vars)
{
	ft_putchar_fd('-', 2);
	ft_putstr_fd(vars.executer_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (2);
}

int	heredoc_error(int line_num, t_vars vars)
{
	ft_putchar_fd('-', 2);
	ft_putstr_fd(vars.executer_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putnbr_fd(line_num, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `EOF')\n", 2);
	return (2);
}
