/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:37:51 by asirenko          #+#    #+#             */
/*   Updated: 2019/08/01 17:38:49 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_left(char **line, char **after)
{
	char *tmp;

	tmp = *line;
	MALCHECKV((*line = ft_strdup(*after)));
	free(tmp);
	free(*after);
}

static char		*ft_before(char *str)
{
	char	*s;
	int		i;
	int		k;

	k = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	MALCHECKC((s = (char *)malloc(sizeof(char) * (i + 1))));
	while (k < i)
	{
		s[k] = str[k];
		k++;
	}
	s[k] = '\0';
	return (s);
}

static char		*ft_after(char *str)
{
	char	*s;
	int		i;
	int		k;

	k = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	MALCHECKC((s = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1))));
	while (str[i])
		s[k++] = str[i++];
	s[k] = '\0';
	return (s);
}

static void		ft_makeword(char **line, int *ret, char **after, int fd)
{
	char buf[BUFF_SIZE + 1];
	char *tmp;
	char *tmp2;

	*ret = 1;
	while (*ret > 0)
	{
		*ret = read(fd, buf, BUFF_SIZE);
		buf[*ret] = '\0';
		if (ft_strchr(buf, '\n'))
			break ;
		tmp = *line;
		MALCHECKV((*line = ft_strjoin(tmp, buf)));
		free(tmp);
	}
	if (ft_strchr(buf, '\n') || *ret < BUFF_SIZE)
	{
		tmp = *line;
		tmp2 = ft_before(buf);
		MALCHECKV((*line = ft_strjoin(*line, tmp2)));
		free(tmp2);
		free(tmp);
		MALCHECKV((*after = ft_after(buf)));
	}
}

int				get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			ret;
	static char	*after[DESCRIPTORS];
	char		*tmp;

	if (fd < 0 || BUFF_SIZE < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	*line = ft_strnew(1);
	tmp = *line;
	if (after[fd] && !ft_strchr(after[fd], '\n'))
		ft_left(line, &after[fd]);
	if (after[fd] && ft_strchr(after[fd], '\n'))
	{
		MALCHECKI((*line = ft_before(after[fd])));
		free(tmp);
		tmp = after[fd];
		MALCHECKI((after[fd] = ft_after(after[fd])));
		free(tmp);
		return (1);
	}
	ft_makeword(line, &ret, &after[fd], fd);
	if (ret == 0 && ft_strcmp(*line, "") == 0)
		return (0);
	return (1);
}
