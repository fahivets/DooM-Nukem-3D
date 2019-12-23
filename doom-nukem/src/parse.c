/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 02:15:15 by ooliinyk          #+#    #+#             */
/*   Updated: 2019/10/16 22:39:40 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	binary_read(t_binary *b)
{
	int		i;

	i = -1;
	b->num_files = 0;
	b->fd = open(b->filename, O_RDONLY);
	if (b->fd <= 0)
	{
		ft_putendl("No binary file");
		exit(0);
	}
	b->data_len = lseek(b->fd, (size_t)0, SEEK_END);
	b->buff = (char*)malloc(sizeof(char) *
		b->data_len);
	close(b->fd);
	b->fd = open(b->filename, O_RDONLY);
	read(b->fd, b->buff, b->data_len);
	close(b->fd);
}

void	num_of_files(t_binary *b)
{
	int		i;
	char	*str;

	i = -1;
	str = (char*)malloc(sizeof(char) * b->data_len);
	while (++i < b->data_len)
	{
		str[i] = b->buff[i];
		if (b->buff[i] == '\0')
			str[i] = '.';
	}
	b->new_buff = ft_strsplit(str, ' ');
	free(str);
	i = -1;
	while (b->new_buff[++i])
		if (ft_strcmp(b->new_buff[i], "filename:") == 0)
			b->num_files++;
	if (b->num_files <= 0 && b->fd > 0)
	{
		ft_putendl("No files in binary");
		exit(0);
	}
}

void	parse_data(t_binary *b)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	b->file = (t_file*)malloc(sizeof(t_file) * b->num_files);
	while (i < b->num_files)
	{
		while (b->new_buff[++j])
		{
			if (ft_strcmp(b->new_buff[j], "filename:") == 0)
			{
				b->file[i].name = ft_strdup(b->new_buff[j + 1]);
				b->file[i].ext = ft_strchr(b->file[i].name, '.');
			}
			if (ft_strcmp(b->new_buff[j], "len_of_file:") == 0)
			{
				b->file[i].data_len = ft_atoi(b->new_buff[j + 1]);
				i++;
			}
			free(b->new_buff[j]);
		}
	}
}
