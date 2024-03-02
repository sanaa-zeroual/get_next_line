/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeroual <szeroual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 01:42:34 by szeroual          #+#    #+#             */
/*   Updated: 2024/02/24 03:31:39 by szeroual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_s;
	char	*result;

	i = 0;
	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		result = (char *)malloc((ft_strlen(s + start) + 1) * sizeof(char));
	else
		result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (s[start] && i < len)
	{
		result[i] = s[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}

char	*readfile(int fd, char *str)
{
	char		*buff;
	ssize_t		readbytes;

	readbytes = 1;
	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (readbytes != 0 && !ft_strchr(str, '\n'))
	{
		readbytes = read(fd, buff, BUFFER_SIZE);
		if (readbytes == -1)
		{
			free (str);
			free(buff);
			return (NULL);
		}
		buff[readbytes] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*extarct_line(char *buff)
{
	int		i;
	char	*line;

	i = 0;
	if (buff[i] == '\0')
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_rest(char *save)
{
	int		i;
	char	*s;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free (save);
		return (NULL);
	}
	i++;
	s = ft_substr(save, i, strlen(save) -i + 1);
	free(save);
	return (s);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*read_line[MAX_FD];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	else
		read_line[fd] = readfile(fd, read_line[fd]);
	if (!read_line[fd])
		return (NULL);
	line = extarct_line(read_line[fd]);
	read_line[fd] = get_rest(read_line[fd]);
	return (line);
}
