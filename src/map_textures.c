/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:24:21 by sdukic            #+#    #+#             */
/*   Updated: 2023/02/12 19:02:02 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/map.h"
#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "MLX42.h"
#include "./include/player.h"
#include "./include/colors.h"
#include "./include/my_math.h"
#include "../lib/libft/libft.h"
#include "./include/my_error.h"
#include <math.h>

char	*steves_get_next_line(int fd)
{
	char	*string;
	char	*copy;

	string = malloc(10000);
	copy = string;
	while (read(fd, copy, 1) > 0)
	{
		if (*copy == '\n')
			break ;
	copy++;
	}
	if (copy > string)
	{
		*copy = 0;
		return (string);
	}
	else
	{
		free(string);
		return (NULL);
	}
}

t_int_vector	get_texture_dim_in_file(char *map_file)
{
	t_int_vector	dim;
	char			*line;
	int				fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		my_error("Could not open map file");
	dim.y = 0;
	dim.x = 0;
	line = steves_get_next_line(fd);
	while (line)
	{
		dim.x = fmaxf(dim.x, (int)strlen(line));
		dim.y++;
		free(line);
		line = steves_get_next_line(fd);
	}
	free(line);
	close(fd);
	return (dim);
}

char	**allocate_map_memory(t_int_vector dim)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * (dim.y + 1));
	i = 0;
	while (i < dim.y)
	{
		map[i] = malloc(sizeof(char) * (dim.x + 1));
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	read_texture_from_file(char **map, int fd)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	line = steves_get_next_line(fd);
	while (line)
	{
		j = 0;
		while (line[j] && line[j] != '\n')
		{
			map[i][j] = line[j];
			j++;
		}
		map[i][j] = 0;
		i++;
		free(line);
		line = steves_get_next_line(fd);
	}
	free(line);
}

char	**init_texture(char *map_file)
{
	int				fd;
	char			**map;
	t_int_vector	dim;

	dim = get_texture_dim_in_file(map_file);
	if (dim.x == 0 || dim.y == 0)
		my_error("Texture file is empty");
	fd = open(map_file, O_RDONLY);
	map = allocate_map_memory(dim);
	read_texture_from_file(map, fd);
	close(fd);
	return (map);
}
