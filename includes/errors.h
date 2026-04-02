/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:30:09 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/02 21:52:05 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

int	exit_error(char *arg);
int	cd_dir_error(char *dir);
int	args_error(char *fn);
int	export_key_error(char *key);
int	quotes_error(void);
int	redir_error(char s);
int file_error(char *file);

#endif
