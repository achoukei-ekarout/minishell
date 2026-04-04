/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukei <achoukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:30:09 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/04 18:09:05 by achoukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

int	exit_error(char *arg);
int	cd_dir_error(char *dir);
int	args_error(char *fn);
int	export_key_error(char *key);
int	quotes_error(t_vars vars);
int	redir_error(char s, t_vars vars);
int file_error(char *file, t_vars vars);
int	heredoc_error(int line_num, t_vars vars);

#endif
