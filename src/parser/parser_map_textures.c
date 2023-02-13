/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:28:42 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/14 00:30:06 by bogunlan         ###   ########.fr       */
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

int	check_text_path(char *text_id, char *text_path, t_map_parsing *map)
{
	int		fd;
	char	*tmp_path;

	tmp_path = ft_substr(text_path, 0, ft_strlen(text_path) - 1);
	fd = open(tmp_path, O_RDONLY);
	if (fd == -1)
	{
		map->text_error = 1;
		free(tmp_path);
		return (file_error);
	}
	if (check_texture(fd, tmp_path) != no_errors)
		return (texture_error);
	close(fd);
	if (strncmp(text_id, "NO", 3) == 0)
		map->textures.north_path = ft_strdup(tmp_path);
	else if (strncmp(text_id, "SO", 3) == 0)
		map->textures.south_path = ft_strdup(tmp_path);
	else if (strncmp(text_id, "WE", 3) == 0)
		map->textures.west_path = ft_strdup(tmp_path);
	else if (strncmp(text_id, "EA", 3) == 0)
		map->textures.east_path = ft_strdup(tmp_path);
	free(tmp_path);
	return (no_errors);
}

int	check_text_surface(t_map_parsing *map, char **split)
{
	if (map->textures.floor_id == 1 && !map->floor_vals_set)
	{
		if (parse_map_floor(split[1], map) != no_errors)
			return (map_error);
	}
	else if (map->textures.ceiling_id == 1 && !map->ceiling_vals_set)
	{
		if (parse_map_ceiling(split[1], map) != no_errors)
			return (map_error);
	}
	return (no_errors);
}

int	is_text_id_valid(char **split, t_map_parsing *map)
{
	if (check_text_id(split[0], map) != no_errors)
	{
		ft_free(split);
		return (elements_error);
	}
	return (no_errors);
}

int	is_text_path_valid(char **split, t_map_parsing *map)
{
	int	error;

	error = check_text_path(split[0], split[1], map);
	if (error)
	{
		ft_free(split);
		return (error);
	}
	return (no_errors);
}
