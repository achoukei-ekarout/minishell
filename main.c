/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:32:44 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/16 01:23:46 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_handler(int sig)
{
    (void)sig;

    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_env	**env;
	t_env	**exp;
	char	*input;
	char	*path;

	if (!argc || !argv || !*envp)
		return (0);
	signal(SIGINT, sigint_handler);
    rl_catch_signals = 0;
	env = environ_init(envp);
	exp = exp_init(env);
	rl_catch_signals = 0;
	while (1)
	{
		path = ft_strjoin(get_env_value(env, "PWD"), "$ ");
		input = readline(path);
		if (!input)
			break ;
		if (!*input)
			continue ;
		if (*input)
			add_history(input);
		if (!ft_strncmp(input, "pwd", 3))
			ft_pwd(env);
		else if(!ft_strncmp(input, "cd", 2))
		{
			char *arg = ft_substr(input, 3, ft_strlen(input) - 3);
			ft_cd(arg, env);
			free(arg);
		}
		else if (!ft_strncmp(input, "env", 3))
			ft_env(env);
		else if (!ft_strncmp(input, "unset", 5))
		{
			char *arg = ft_substr(input, 6, ft_strlen(input) - 6);
			ft_unset(arg, env, exp);
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
			ft_export(arg, env, exp);
			free(arg);
		}
		else if (!ft_strncmp(input, "exit", 4))
		{
			char *arg = ft_substr(input, 5, ft_strlen(input) - 5);
			ft_exit(arg);
			free(arg);
		}
		free(input);
		free(path);
	}
	free(path);
	rl_clear_history();
	env_clear(env);
	env_clear(exp);
	return (0);
}
