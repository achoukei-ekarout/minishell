/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 08:43:13 by achoukei          #+#    #+#             */
/*   Updated: 2026/04/12 13:41:11 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	proccess_heredoc(t_ast *node, t_vars *vars, t_gc **head_gc)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
		proccess_node_heredoc(node, vars, head_gc);
	else if (node->type == NODE_PIPE)
	{
		proccess_heredoc(node->left, vars, head_gc);
		proccess_heredoc(node->right, vars, head_gc);
	}
}

void	proccess_node_heredoc(t_ast *node, t_vars *vars, t_gc **head_gc)
{
	t_redir	*redir;

	redir = node->redir;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC || redir->type == TOKEN_HEREDOC_NOEXP)
		{
			redir->fd = apply_heredoc(redir->file, redir->type, vars, head_gc);
			if (redir->fd == -1)
				return ;
		}
		redir = redir->next;
	}
}

void    setup_signals_heredoc(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
}

void    restore_terminal(void)
{
    struct termios  term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ECHO | ICANON | IEXTEN | ISIG);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
	write(1, "^C", 2);
    rl_on_new_line();
    rl_replace_line("", 0);
    // rl_redisplay();
    write(STDOUT_FILENO, "\n", 1);
}

int	apply_heredoc(char *delimeter, t_token_type type, t_vars *vars,
		t_gc **head_gc)
{
	int	fd[2];
	int	pid;
	int	status;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		setup_signals_heredoc();
		if (type == TOKEN_HEREDOC)
			while (heredoc_readline_expand(delimeter, fd[1], vars, head_gc))
				continue ;
		else
			while (heredoc_readline(delimeter, fd[1], vars))
				continue ;
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_prompt);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(fd[0]);
		g_signal = SIGINT;
		restore_terminal();
		return (-1);
	}
	return (fd[0]);
}

int	check_expand(t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'' || token->value[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

void	check_heredoc(t_token **tokens, t_gc **head_gc)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC && current->next)
		{
			if (check_expand(current->next))
			{
				current->type = TOKEN_HEREDOC_NOEXP;
				current->next->value = expand_heredoc(
						current->next->value, head_gc);
			}
			else
				current->type = TOKEN_HEREDOC;
		}
		current = current->next;
	}
}
