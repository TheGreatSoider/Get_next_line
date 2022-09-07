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

// "Hello, this is Jack. I am here to be a test subject to getting the next 
// line for this project"

#include "get_next_line.h"

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
	while (ft_strchr(str, '\n') && i != 0)
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

char	*cpy_del(char *str, char **temp)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	j = 0;
	while (str[i++] != '\0')
		j++;
	temp = ft_calloc((j - 1), sizeof(char));
	*temp = ft_substr(str, (i - j + 1), (j - 1));
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i++] == '\n')
		line[i] = str[i];
	free(str);
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
	static char	*str;
	char		**temp;
	char		*line;

	temp = 0;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	str = reading(fd, str);
	if (str == 0)
		return (NULL);
	line = cpy_del(str, temp);
	str = *temp;
	free(temp);
	return (line);
}
