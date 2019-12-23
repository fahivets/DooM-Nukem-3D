/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 18:31:37 by ooliinyk          #+#    #+#             */
/*   Updated: 2019/10/16 20:29:29 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		bytes_len(t_binaryp *b)
{
	int		i;

	i = -1;
	while (++i < b->n_file)
	{
		b->file[i].data_len = 0;
		b->file[i].fd = open(b->file[i].filename, O_RDONLY);
		b->file[i].data_len = lseek(b->file[i].fd, (size_t)0, SEEK_END);
		close(b->file[i].fd);
	}
}

void		packing(t_binaryp *b)
{
	int	i;

	i = -1;
	while (++i < b->n_file)
	{
		b->file[i].fd = open(b->file[i].filename, O_RDONLY);
		b->fin_data_len += b->file[i].data_len;
		b->file[i].buff = (unsigned char *)malloc(sizeof(unsigned char)
			* b->file[i].data_len);
		read(b->file[i].fd, b->file[i].buff, b->file[i].data_len);
		close(b->file[i].fd);
	}
}

static void	free_d(t_binaryp *b)
{
	int i;

	i = -1;
	while (++i < b->n_file)
	{
		free(b->file[i].filename);
		free(b->file[i].buff);
	}
	free(b->file);
}

void		pack(void)
{
	int				i;
	t_binaryp		binary;
	DIR				*dir;
	struct dirent	*ent;

	binary.n_file = 0;
	i = -1;
	dir = opendir("./assets");
	if (dir)
	{
		while ((ent = readdir(dir)) != NULL)
			if (ent->d_name[0] != '.')
				binary.n_file++;
		rewinddir(dir);
		binary.file = (t_filep *)malloc(sizeof(t_filep) * binary.n_file);
		while ((ent = readdir(dir)) != NULL)
			if (ent->d_name[0] != '.')
				binary.file[++i].filename =
			ft_strjoin("./assets/", ent->d_name);
		closedir(dir);
	}
	bytes_len(&binary);
	packing(&binary);
	ft_putsuperstr_fd(&binary);
	free_d(&binary);
}
