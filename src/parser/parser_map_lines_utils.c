/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_lines_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:54:00 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/14 00:22:52 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/gnl/get_next_line.h"
#include "../../lib/libft/libft.h"
#include "../include/parser.h"

int	split_count(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	is_element(char *line)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (map_error);
	if (split[0][0] != ' ' && split[0][0] != 'N' && split[0][0] != 'S' && \
split[0][0] != 'W' && split[0][0] != 'E' && split[0][0] != 'F' && \
split[0][0] != 'C' && split[0][0] != '0' && split[0][0] != '1'
	)
	{
		ft_free(split);
		return (texture_error);
	}
	ft_free(split);
	return (no_errors);
}

int	check_text_id(char *text_id, t_map_parsing *map)
{
	int	error;

	error = no_errors;
	if (strncmp(text_id, "NO", 3) == 0)
		map->textures.north_id += 1;
	else if (strncmp(text_id, "SO", 3) == 0)
		map->textures.south_id += 1;
	else if (strncmp(text_id, "WE", 3) == 0)
		map->textures.west_id += 1;
	else if (strncmp(text_id, "EA", 3) == 0)
		map->textures.east_id += 1;
	else if (strncmp(text_id, "F", 2) == 0)
		map->textures.floor_id += 1;
	else if (strncmp(text_id, "C", 2) == 0)
		map->textures.ceiling_id += 1;
	else
	{
		error = elements_error;
	}
	return (error);
}

int	is_wall_texture_valid(char *text_line)
{
	int	i;
	int	error;

	i = 0;
	if (!text_line)
		return (no_errors);
	while (text_line[i])
	{
		if (text_line[i] != '1' && text_line[i] != '0' && text_line[i] != '\n')
			return (texture_error);
		i++;
	}
	if (strchr(text_line, '1') != NULL || strchr(text_line, '0') != NULL || \
strchr(text_line, '\n') != NULL)
		error = no_errors;
	else
		error = texture_error;
	return (error);
}

int	check_texture(int fd, char *texture_path)
{
	int		i;
	char	*texture_line;

	i = 0;
	while (1)
	{
		texture_line = get_next_line(fd);
		if (texture_line)
			i++;
		if (is_wall_texture_valid(texture_line) != no_errors || i == 0)
		{
			free(texture_line);
			free(texture_path);
			close(fd);
			return (texture_error);
		}
		if (!texture_line)
			break ;
		free(texture_line);
	}
	return (no_errors);
}
