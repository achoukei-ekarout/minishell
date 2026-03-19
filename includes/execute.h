/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:28:46 by user              #+#    #+#             */
/*   Updated: 2026/03/19 22:24:36 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "parse.h"

void	execute_ast(t_ast *node, char **envp);
void	execute_pipe(t_ast *node, char **envp);
void	execute_command(t_ast *node, char **envp,char **paths);
void	apply_redirections(t_redir *redir);
char	*get_path(char **envp);

#endif