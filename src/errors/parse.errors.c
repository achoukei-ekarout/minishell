/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:29:16 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/11 01:13:45 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_error(t_vars vars)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(vars.executer_name, ": ");
	temp2 = ft_strjoin(temp1, "error: unclosed quote\n");
	ft_putstr_fd(temp2, 2);
	free(temp1);
	free(temp2);
	return (-1);
}

int	redir_error(char s, t_vars vars)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(vars.executer_name, ": ");
	temp2 = ft_strjoin(temp1, "syntax error near unexpected token `");
	free(temp1);
	ft_putstr_fd(temp2, 2);
	if (s)
		ft_putchar_fd(s, 2);
	else
		ft_putstr_fd("newline", 2);
	free(temp2);
	ft_putstr_fd("\'\n", 2);
	return (2);
}

int	file_error(char *file, t_vars vars)
{
	char *temp1;
	char *temp2;
	
	temp1 = ft_strjoin(vars.executer_name, ": ");
	temp2 = ft_strjoin(temp1, file);
	free(temp1);
	temp1 = ft_strjoin(temp2," : No such file or directory\n");
	ft_putstr_fd(temp1, 2);
	free(temp1);
	free(temp2);
	return (2);
}

int	heredoc_error(t_vars vars)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(vars.executer_name, ": ");
	temp2 = ft_strjoin(temp1, "warning: here-document at line ");
	ft_putstr_fd(temp2, 2);
	ft_putnbr_fd(vars.line_counter, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `EOF')\n", 2);
	free(temp1);
	free(temp2);
	return (2);
}

void	is_dir(char *dir, t_vars vars)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(vars.executer_name, ": ");
	temp2 = ft_strjoin(temp1, dir);
	free(temp1);
	temp1 = ft_strjoin(temp2, ": Is a directory\n");
	ft_putstr_fd(temp1, 2);
	free(temp1);
	free(temp2);
}
