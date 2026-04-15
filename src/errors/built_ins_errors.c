/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:34:20 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/15 13:26:52 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_error(char *arg, t_vars vars)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(vars.executer_name, ": ");
	temp2 = ft_strjoin(temp1, "exit: ");
	free(temp1);
	temp1 = ft_strjoin(temp2, arg);
	free(temp2);
	temp2 = ft_strjoin(temp1, ": numeric argument required\n");
	ft_putstr_fd(temp2, 2);
	free(temp1);
	free(temp2);
	return (2);
}

int	cd_dir_error(char *dir, t_vars vars)
{
	char	*temp;

	temp = ft_strjoin(vars.executer_name, ": cd: ");
	ft_putstr_fd(temp, 2);
	perror(dir);
	free(temp);
	return (1);
}

int	args_error(char *fn, t_vars vars)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(vars.executer_name, ": ");
	temp2 = ft_strjoin(temp1, fn);
	free(temp1);
	temp1 = ft_strjoin(temp2, ": too many arguments\n");
	ft_putstr_fd(temp1, 2);
	free(temp1);
	free(temp2);
	return (1);
}

int	export_key_error(char *key, t_vars vars)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(vars.executer_name, ": ");
	temp2 = ft_strjoin(temp1, "export: `");
	free(temp1);
	temp1 = ft_strjoin(temp2, key);
	free(temp2);
	temp2 = ft_strjoin(temp1, "': not a valid identifier\n");
	ft_putstr_fd(temp2, 2);
	free(temp1);
	free(temp2);
	return (1);
}
