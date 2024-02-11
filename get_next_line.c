#define BUFFER_SIZE 3
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
char	*readfile_rest(char *left_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (!left_str[i])
	{
		free(left_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(left_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (left_str[i])
		str[j++] = left_str[i++];
	str[j] = '\0';
	free(left_str);
	return (str);
}
static void	ft_strcpy(char *destination, const char *source)
{
	while (*source != '\0')
	{
		*destination = *source;
		source++;
		destination++;
	}
	*destination = '\0';
}

static void	ft_strcat(char *dest, const char *src)
{
	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	result = (char *)malloc((ft_strlen(s2) + ft_strlen(s1) + 1) * sizeof(char));
	if (result != NULL)
	{
		ft_strcpy(result, s1);
		ft_strcat(result, s2);
	}
	return (result);
}
char    *ft_getline(char *full_str)
{
    int        i;
    char    *line;

    i = 0;
    if (!full_str[i])
        return (NULL);
    while (full_str[i] && full_str[i] != '\n')
        i++;
    line = (char *)malloc(sizeof(char) * (i + 2));
    if (!line)
        return (NULL);
    i = 0;
    while (full_str[i] && full_str[i] != '\n')
    {
        line[i] = full_str[i];
        i++;
    }
    if (full_str[i] == '\n')
    {
        line[i] = full_str[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}
char *readfile(int fd, char *buff)
{
    char *str = NULL;
    buff = malloc(BUFFER_SIZE + 1);
    if(!buff)
    return NULL;
     int readbytes = 1;
    while (readbytes != 0 && !strchr(buff, '\n'))
    {
       readbytes = read(fd, buff, BUFFER_SIZE);
    if((readbytes = -1) || (readbytes = 0))
    {
    free (buff);
    return NULL;
    }
    buff[readbytes] = '\0';
    str = ft_strjoin(buff, str);
    }
    free (str);
    return buff;
}
char *get_next_line(int fd)
{
    char *line;
    static char *read_line;
   if(fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
        else
    read_line = readfile(fd, read_line);
   if(!read_line)
   return NULL;
   line = readfile_rest(read_line);
   read_line = ft_new_left_str(read_line);
   return line;
}
int main()
{
    int fd = open("sanaa.txt", O_RDONLY);
    char *line = get_next_line(fd);
    printf("%s", line);
}