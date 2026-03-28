/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 08:43:13 by achoukei          #+#    #+#             */
/*   Updated: 2026/03/27 21:52:05 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    proccess_heredoc(t_ast *node)
{
    if (!node)
        return ;
    
    if (node->type == NODE_COMMAND)
        proccess_node_heredoc(node);
    else if (node->type == NODE_PIPE)
    {
        proccess_heredoc(node->left);
        proccess_heredoc(node->right);
    }
}

void    proccess_node_heredoc(t_ast *node)
{
    t_redir *redir;

    redir = node->redir;
    while (redir)
    {
        if (redir->type == TOKEN_HEREDOC)
            redir->fd = apply_heredoc(redir->file);
        redir = redir->next;
    }
}

int apply_heredoc(char *delimeter)
{
    int     fd[2];
    char    *line;

    if (pipe(fd) == -1)
        perror("pipe");
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, delimeter) == 0)
        {
            free(line);
            break;
        }
        write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
        free(line);
    }
    close(fd[1]);
    return (fd[0]);
}
