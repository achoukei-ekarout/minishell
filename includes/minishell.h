/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:22:44 by ekarout           #+#    #+#             */
/*   Updated: 2026/04/01 16:33:09 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "built_ins.h"
# include "data.h"
# include "environ.h"
# include "execute.h"
# include "garbage_collector.h"
# include "parse.h"
# include "errors.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "export_environ.h"
# include "expansion.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>

#endif