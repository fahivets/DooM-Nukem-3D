/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:58:14 by ooliinyk          #+#    #+#             */
/*   Updated: 2019/10/16 15:16:53 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _UNPACK_H
# define _UNPACK_H

typedef struct s_file	t_file;
typedef struct s_binary	t_binary;

struct					s_file
{
	int					fd;
	int					data_len;
	char				*buff;
	char				*name;
	char				*ext;
	int					start;
};

struct					s_binary
{
	int					fd;
	char				**new_buff;
	char				*filename;
	int					data_len;
	char				*buff;
	int					num_files;
	t_file				*file;
};

void					binary_read(t_binary *b);
void					num_of_files(t_binary *b);
void					parse_data(t_binary *b);

#endif
