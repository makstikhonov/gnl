/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:45:04 by max               #+#    #+#             */
/*   Updated: 2021/01/07 12:50:49 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		read_from_fd(char **rmdr, char **p_n, int fd)
{
	char		*buf;
	char		*tmp;
	int			rs;

	if ((buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
	{
		free(*rmdr);
		return (-1);
	}
	rs = 1;
	if (!*p_n && (rs = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		buf[rs] = '\0';
		tmp = *rmdr;
		if (!(*rmdr = ft_strjoin(tmp, buf)))
		{
			free(buf);
			free(*rmdr);
			return (-1);
		}
		free(tmp);
	}
	free(buf);
	return (rs);
}

int		f_n_find(char **line, char **p_n, char **rmdr)
{
	**p_n = '\0';
	if (!(*line = ft_strdup(*rmdr)))
	{
		free(*rmdr);
		return (-1);
	}
	(*p_n)++;
	ft_strlcpy(*rmdr, *p_n, ft_strlen(*p_n) + 1);
	return (1);
}

int		f_last(char **line, char **rmdr)
{
	if (!(*line = ft_strdup(*rmdr)))
	{
		free(*rmdr);
		return (-1);
	}
	*rmdr[0] = '\0';
	free(*rmdr);
	*rmdr = NULL;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int			rs;
	char		*p_n;
	static char	*rmdr;

	rs = 1;
	if (line == NULL || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (!rmdr)
	{
		if ((rmdr = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
			return (-1);
		rmdr[0] = '\0';
	}
	p_n = ft_strchr(rmdr, '\n');
	while (rs >= 0)
	{
		if((rs = read_from_fd(&rmdr, &p_n, fd)) < 0)
			return (-1);
		if ((p_n = ft_strchr(rmdr, '\n')))
			return (f_n_find(line, &p_n, &rmdr));
		if (rs == 0)
			return (f_last(line, &rmdr));
	}
	return (0);
}
