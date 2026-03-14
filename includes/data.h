/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:06:31 by ekarout           #+#    #+#             */
/*   Updated: 2026/03/12 02:06:39 by ekarout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef struct s_env_data
{
	char			*key;
	char			*value;
}	t_env_data;

typedef struct s_env
{
	t_env_data		*data;
	struct s_env	*next;
}	t_env;

typedef struct s_exp
{
	char			*data;
	struct s_exp	*next;
}	t_exp;

#endif
