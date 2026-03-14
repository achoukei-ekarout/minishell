/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:32:44 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/12 22:00:53 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	**env;
	char	*input;
	char	*path;

	if (!argc || !argv || !*envp)
		return (0);
	env = environ_init(envp);
	while (1)
	{
		path = ft_strjoin(get_env_value(env, "PWD"), "$ ");
		input = readline(path);
		if (!input)
			break ;
		if (!strcmp(input, "pwd"))
			ft_pwd(env);
		else if(!ft_strncmp(input, "cd", 2))
		{
			char *arg = ft_substr(input, 3, ft_strlen(input) - 3);
			ft_cd(arg, env);
			free(arg);
		}
		else if (!strcmp(input, "env"))
			ft_env(env);
		else if (!ft_strncmp(input, "unset", 5))
		{
			char *arg = ft_substr(input, 6, ft_strlen(input) - 6);
			ft_unset(arg, env);
			free(arg);
		}
		else if (!ft_strncmp(input, "echo", 4))
		{
			char *arg = ft_substr(input, 5, ft_strlen(input) - 5);
			ft_echo(arg);
			free(arg);
		}
		else if (!ft_strncmp(input, "export", 6))
		{
			char *arg = ft_substr(input, 7, ft_strlen(input) - 7);
			ft_export(arg, env);
			free(arg);
		}
		free(input);
		free(path);
	}
	free(path);
	rl_clear_history();
	env_clear(env);
	return (0);
}
