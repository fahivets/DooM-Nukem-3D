/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:57:29 by ooliinyk          #+#    #+#             */
/*   Updated: 2019/10/16 22:40:59 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static char	*ft_new_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

static void	find_start(t_binary *b)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	j = -1;
	while (i < b->num_files)
	{
		while (++j < b->data_len)
		{
			len = ft_strlen(b->file[i].ext);
			if (ft_strncmp(&b->buff[j], b->file[i].ext, len) == 0)
			{
				b->file[i].start = j;
				b->file[i].start += (int)len + 2;
				i++;
				break ;
			}
		}
	}
}

static void	unpack2(t_binary *b)
{
	char	*file;
	int		i;
	int		check;

	if ((check = open("./res", O_RDONLY)) < 0)
		mkdirat(AT_FDCWD, "res", 0777);
	close(check);
	i = -1;
	while (++i < b->num_files)
	{
		file = ft_strjoin("./res", b->file[i].name);
		b->file[i].fd = open(file, O_RDWR | O_CREAT, S_IREAD | S_IWRITE);
		free(file);
		b->file[i].buff = ft_new_strsub(b->buff, b->file[i].start,
			b->file[i].data_len);
		write(b->file[i].fd, b->file[i].buff, b->file[i].data_len);
		free(b->file[i].buff);
		close(b->file[i].fd);
	}
}

static void	free_d(t_binary *b)
{
	int	i;

	i = 0;
	while (i < b->num_files)
	{
		free(b->file[i].name);
		i++;
	}
	free(b->file);
}

void		unpack(char *filename)
{
	t_binary	b;

	b.filename = filename;
	binary_read(&b);
	num_of_files(&b);
	parse_data(&b);
	find_start(&b);
	unpack2(&b);
	free_d(&b);
	free(b.new_buff);
	free(b.buff);
}
