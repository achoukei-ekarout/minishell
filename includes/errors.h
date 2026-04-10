/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:30:09 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/11 01:15:03 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

int		exit_error(char *arg, t_vars vars);
int		cd_dir_error(char *dir, t_vars vars);
int		args_error(char *fn, t_vars vars);
int		export_key_error(char *key, t_vars vars);
int		quotes_error(t_vars vars);
int		redir_error(char s, t_vars vars);
int		file_error(char *file, t_vars vars);
int		heredoc_error(t_vars vars);
void	is_dir(char *dir, t_vars vars);

#endif
