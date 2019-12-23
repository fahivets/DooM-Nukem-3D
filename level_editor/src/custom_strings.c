/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_strings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 02:06:14 by ooliinyk          #+#    #+#             */
/*   Updated: 2019/10/16 20:29:57 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	filename(t_binaryp *b, char **tmp, char **str, int *i)
{
	*tmp = ft_strjoin(" filename: ", ft_strrchr(b->file[*i].filename, '/'));
	*str = *tmp;
	free(*tmp);
	*tmp = ft_strjoin(*str, " ");
	*str = *tmp;
	free(*tmp);
}

void	file_len(t_binaryp *b, char **tmp, char **len_of_file, int *i)
{
	*tmp = ft_itoa(b->file[*i].data_len);
	*len_of_file = *tmp;
	free(*tmp);
	*tmp = ft_strjoin(" len_of_file: ", *len_of_file);
	*len_of_file = *tmp;
	free(*tmp);
	*tmp = ft_strjoin(*len_of_file, " ");
	*len_of_file = *tmp;
	free(*tmp);
}

void	ft_putsuperstr_fd(t_binaryp *b)
{
	int		i;
	size_t	len;
	char	*str;
	char	*tmp;
	char	*len_of_file;

	i = -1;
	len = 0;
	str = NULL;
	tmp = NULL;
	system("touch map.udt");
	b->dst = open("map.udt", O_RDWR);
	while (++i < b->n_file)
	{
		filename(b, &tmp, &str, &i);
		len = ft_strlen(str) + 1;
		write(b->dst, str, len);
		write(b->dst, b->file[i].buff, b->file[i].data_len);
		file_len(b, &tmp, &len_of_file, &i);
		len = ft_strlen(len_of_file) + 1;
		write(b->dst, len_of_file, len);
	}
	close(b->dst);
}
