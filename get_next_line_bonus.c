/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:04:58 by cocheong          #+#    #+#             */
/*   Updated: 2022/08/30 16:04:58 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/*
Reads whatever in fd and stores in buff temporarily
If error, free and return NULL
Str takes whatever it already has and joins with buff.
BUF_SIZE = 8
Hello-World\nBye-Bye-World
1st:
Str = Hello-Wo\0
2nd:
Str = Hello-Wo + rld\nBye- = Hello-World\nBye-\0
*/

char	*reading(int fd, char *str)
{
	char	*buff;
	int		i;

	buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (buff == 0)
		return (NULL);
	i = 1;
	while (!ft_strchr(str, '\n') && i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			return (NULL);
		}
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

/*
temp keeps the latter portion of str post \n.
line copies the str up until \n
Using example above
temp = Bye-
line = Hello-World\n
*/

char	*cpy_del(char **str)
{
	char	*temp;
	char	*line;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while ((*str)[i] != '\0' && (*str)[i] != '\n')
		i++;
	if ((*str)[i] == '\0')
	{
		line = ft_substr(*str, 0, (i + 1));
		free(*str);
		*str = NULL;
		return (0);
	}
	line = ft_substr(*str, 0, (i + 1));
	temp = ft_substr(*str, i + 1, ft_strlen(*str));
	free(*str);
	*str = ft_substr(temp, 0, (i + 1));
	return (line);
}
/*
From example above, 
str = Hello-World\nBye-\0
line = Bye-
temp is pointed to the function above which is Bye-
str = temp = Bye-.
Free temp to prevent leaks
*/

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (str[fd] == 0)
		str[fd] = ft_calloc(1, 1);
	str[fd] = reading(fd, str[fd]);
	if (str == 0)
		return (NULL);
	line = cpy_del(&str[fd]);
	return (line);
}


int main (void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	// char	*str;
	// char	*str2;
	// char	*res;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	// str = reading(fd1, str);
	// printf("%s\n", str);
	// str2 = cpy_del(str);
	// printf("%s\n", str2);
	// printf("%s\n", &*str);
	printf("%s\n", get_next_line(fd1));
	printf("%s\n", get_next_line(fd2));
	printf("%s\n", get_next_line(fd3));
	printf("%s\n", get_next_line(fd1));
	printf("%s\n", get_next_line(fd2));
	printf("%s\n", get_next_line(fd3));
	printf("%s\n", get_next_line(fd1));
	printf("%s\n", get_next_line(fd2));
	printf("%s\n", get_next_line(fd3));
	printf("%s\n", get_next_line(fd1));
	printf("%s\n", get_next_line(fd2));
	printf("%s\n", get_next_line(fd3));
	printf("%s\n", get_next_line(fd1));
	printf("%s\n", get_next_line(fd2));
	printf("%s\n", get_next_line(fd3));
	printf("%s\n", get_next_line(fd1));
	printf("%s\n", get_next_line(fd2));
	printf("%s\n", get_next_line(fd3));
	printf("%s\n", get_next_line(fd1));
	printf("%s\n", get_next_line(fd2));
	printf("%s\n", get_next_line(fd3));
	printf("%s\n", get_next_line(fd1));
	printf("%s\n", get_next_line(fd2));
	printf("%s\n", get_next_line(fd3));
}
