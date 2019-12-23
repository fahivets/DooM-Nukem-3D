/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 22:09:42 by ooliinyk          #+#    #+#             */
/*   Updated: 2019/10/16 19:49:28 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PACK_H
# define _PACK_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <fcntl.h>

typedef struct s_binaryp	t_binaryp;
typedef struct s_filep	t_filep;

struct					s_filep
{
	size_t				data_len;
	int					fd;
	char				*filename;
	unsigned char		*buff;
};

struct					s_binaryp
{
	int					n_file;
	unsigned int		image_count;
	t_filep				*file;
	int					dst;
	size_t				fin_data_len;
};

void					ft_putsuperstr_fd(t_binaryp *b);

#endif
