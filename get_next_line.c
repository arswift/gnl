/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ostrizh <strizh.olga.fi@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:07:02 by ostrizh           #+#    #+#             */
/*   Updated: 2022/05/24 17:49:51 by ostrizh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_line_length(char **str)
{
	char	*ptr;

	ptr = *str;
	while (*ptr)
	{
		if (*ptr == '\n')
			break ;
		ptr++;
	}
	return (ptr - *str);
}

int	get_line(char **fd_buffer, char **line)
{
	char	*ptr_buffer;
	size_t	len;

	len = get_line_length(fd_buffer);
	if (!(*fd_buffer)[len])
	{
		*line = ft_strdup(*fd_buffer);
		ft_strdel(fd_buffer);
	}
	else
	{
		*line = ft_strsub(*fd_buffer, 0, len);
		ptr_buffer = ft_strdup(&((*fd_buffer)[len + 1]));
		free(*fd_buffer);
		*fd_buffer = ptr_buffer;
		if (!(*fd_buffer)[0])
			ft_strdel(fd_buffer);
	}
	return (1);
}

int	handle_result(size_t ret, char **fd_buffer, char **line)
{
	if (ret < 0 || ret > BUFF_SIZE)
		return (-1);
	else if ((ret == 0) && (!*fd_buffer))
	{
		*line = NULL;
		return (0);
	}
	else
		return (get_line(fd_buffer, line));
}

int	handle_buffer(int fd, char **fd_buffer, char **line)
{
	char		*read_buffer;
	char		*ptr_buffer;
	size_t		ret;

	read_buffer = ft_strnew(BUFF_SIZE);
	ret = read(fd, read_buffer, BUFF_SIZE);
	while (ret > 0 && ret <= BUFF_SIZE)
	{
		if (!*fd_buffer)
			*fd_buffer = ft_strdup(read_buffer);
		else
		{
			ptr_buffer = ft_strjoin(*fd_buffer, read_buffer);
			free(*fd_buffer);
			*fd_buffer = ptr_buffer;
		}
		if (ft_strchr(*fd_buffer, '\n'))
			break ;
		ft_bzero(read_buffer, BUFF_SIZE);
		ret = read(fd, read_buffer, BUFF_SIZE);
	}
	ft_strdel(&read_buffer);
	return (handle_result(ret, fd_buffer, line));
}

int	get_next_line(const int fd, char **line)
{
	static char		*lines_buffer[MAX_FD];

	if (BUFF_SIZE < 1 || fd < 0 || fd >= MAX_FD || !line)
		return (-1);
	return (handle_buffer(fd, &(lines_buffer[fd]), line));
}
