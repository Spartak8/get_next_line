/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 13:33:40 by skhachat          #+#    #+#             */
/*   Updated: 2026/02/22 13:33:40 by skhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line(char *str)
{
	char	*newstr;
	size_t	i;

	if (!str || str[0] == '\0')
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	newstr = ft_substr(str, 0, i);
	return (newstr);
}

static char	*get_end(char *str)
{
	char	*newstr;
	size_t	i;

	if (!str || str[0] == '\0')
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	newstr = ft_substr(str, i, ft_strlen(str) - i);
	return (newstr);
}

static char	*readf(int fd, char *remainder)
{
	ssize_t		bytes;
	char		*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (remainder);
	while (!ft_strchr(remainder, '\n'))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		if (bytes < 0)
		{
			free(remainder);
			free(buf);
			return (NULL);
		}
		buf[bytes] = '\0';
		remainder = ft_strjoin(remainder, buf);
		if (!remainder)
			break ;
	}
	free(buf);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder[1024];
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder[fd])
		remainder[fd] = ft_strdup("");
	if (!remainder[fd])
		return (NULL);
	remainder[fd] = readf(fd, remainder[fd]);
	if (!remainder[fd])
		return (NULL);
	line = get_line(remainder[fd]);
	temp = remainder[fd];
	remainder[fd] = get_end(remainder[fd]);
	free(temp);
	if (!line || line[0] == '\0')
	{
		free(line);
		free(remainder[fd]);
		remainder[fd] = NULL;
		return (NULL);
	}
	return (line);
}
