/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:04:09 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/24 12:59:23 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env **env)
{
	char	*pathname;
	char	*home;

	pathname = get_env_value(env, "PWD");
	home = get_env_value(env, "HOME");
	printf("%s%s\n", home, pathname);
	return (0);
}
