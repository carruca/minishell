/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1010/01/08 17:01:19 by tsierra-          #+#    #+#             */
/*   Updated: 2020/11/16 13:10:09 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_line(char **line, char **s)
{
	char	*temp;
	int		l;

	l = 0;
	while ((*s)[l] != '\n' && (*s)[l] != '\0')
		l++;
	if ((*s)[l] == '\n')
	{
		*line = ft_substr(*s, 0, l);
		temp = ft_strdup(&(*s)[l + 1]);
		free(*s);
		*s = temp;
	}
	else
	{
		*line = ft_strdup(*s);
		free(*s);
		*s = NULL;
		return (0);
	}
	return (1);
}

static int	get_output(char **line, int fd, int n_bytes_read, char **s)
{
	if (n_bytes_read < 0)
		return (-1);
	else if (n_bytes_read == 0 && s[fd] == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (get_line(line, &s[fd]));
}

int			get_next_line(int fd, char **line)
{
	int			n_bytes_read;
	char		buff[BUFFER_SIZE + 1];
	char		*temp;
	static char	*next_line[FD_SIZE];

	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buff, 0) < 0)
		return (-1);
	while ((n_bytes_read = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[n_bytes_read] = '\0';
		if (next_line[fd] == NULL)
			next_line[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(next_line[fd], buff);
			free(next_line[fd]);
			next_line[fd] = temp;
		}
		if (ft_strchr(next_line[fd], '\n'))
			break ;
	}
	return (get_output(line, fd, n_bytes_read, next_line));
}
