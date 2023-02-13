/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:36:10 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/13 03:00:51 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*newstr;
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !s2)
		return (NULL);
	newstr = (char *) malloc(sizeof(*s1) * (ft_strlen(s1)+ ft_strlen(s2) + 1));
	if (!newstr)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
	{
		newstr[i] = s1[i];
	}
	j = -1;
	while (s2[++j] != '\0')
	{
		newstr[i++] = s2[j];
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	const char		*p;

	i = 0;
	p = NULL;
	while (1)
	{
		if (s[i] == (unsigned char) c)
		{
			p = &s[i];
			break ;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return ((char *)(p));
}

char	*ft_read(int fd, char *str, char *temp_stash, char *stash)
{
	int	bytes;

	bytes = 1;
	while (bytes != 0)
	{
		bytes = read(fd, str, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(str);
			return (NULL);
		}
		str[bytes] = '\0';
		temp_stash = stash;
		if (!temp_stash)
		{
			temp_stash = malloc(sizeof(char));
			temp_stash[0] = '\0';
		}
		stash = ft_strjoin(temp_stash, str);
		free(temp_stash);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	free(str);
	return (stash);
}

char	*check_stash(int fd, char *stash[], char *str, char *temp_stash)
{
	char	**sliced_string;
	char	*read_line;

	stash[fd] = ft_read(fd, str, temp_stash, stash[fd]);
	if (!stash[fd] || ft_strlen(stash[fd]) < 1)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	if (ft_strchr(stash[fd], '\n'))
	{
		sliced_string = ft_slice(stash[fd], '\n');
		read_line = sliced_string[0];
		free(stash[fd]);
		stash[fd] = sliced_string[1];
		free(sliced_string);
		return (read_line);
	}
	read_line = stash[fd];
	stash[fd] = NULL;
	return (read_line);
}

char	*get_next_line(int fd)
{
	char			*str;
	static char		*stash[256];
	char			*temp_stash;
	char			*line;

	temp_stash = NULL;
	if (fd < 0 || fd > 255 || BUFFER_SIZE <= 0)
		return (NULL);
	str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return (NULL);
	line = check_stash(fd, &stash[fd], str, temp_stash);
	return (line);
}
