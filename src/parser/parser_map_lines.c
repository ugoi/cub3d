/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:54:16 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/14 00:28:59 by bogunlan         ###   ########.fr       */
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

int	is_line_valid(t_map_parsing *map)
{
	char	**split;
	int		error;

	if (is_element(map->line) == 0 && map->all_text_set != 1)
	{
		split = ft_split(map->line, ' ');
		if (!split)
			return (map_error);
		if (is_text_id_valid(split, map) != no_errors)
			return (elements_error);
		if (*(split[0]) != 'F' && *(split[0]) != 'C')
		{
			error = is_text_path_valid(split, map);
			if (error)
				return (error);
		}
		if (check_text_surface(map, split) != no_errors)
		{
			ft_free(split);
			return (map_error);
		}
		ft_free(split);
	}
	return (no_errors);
}

int	is_map_lines_valid(t_map_parsing *map, char **cub_map, int *cub_map_index)
{
	int	i;

	if (check_map_composition(map->line, map->tmp_map) != no_errors)
		return (map_error);
	if (ft_strchr(map->line, '1') || ft_strchr(map->line, '0') || \
	ft_strchr(map->line, 'N') || ft_strchr(map->line, 'S') || \
	ft_strchr(map->line, 'E') || ft_strchr(map->line, 'W'))
	{
		map->at_wall = 1;
		cub_map[*cub_map_index] = ft_substr(map->line, 0, ft_strlen(map->line));
		*cub_map_index += 1;
		i = 0;
		while (map->line[i] != '\0')
		{
			if (map->line[i] == 'N' || map->line[i] == 'S' || \
	map->line[i] == 'E' || map->line[i] == 'W')
			{
				map->player_start_position++;
			}
			i++;
		}
	}
	return (no_errors);
}

int	check_line(t_map_parsing *map, char **cub_map, int *cub_map_index)
{
	int		error;

	if (((*(map->line) == ' ' && (*(map->line + 1)) == '\0') || \
		(*(map->line) == ' ' && (*(map->line + 1)) == ' ')) && \
		(ft_strchr(map->line, '1') == NULL)
	)
		return (map_error);
	if (*(map->line) == '\n' && map->at_wall != 1)
		return (no_errors);
	if (is_element(map->line) != no_errors)
		return (map_error);
	error = is_line_valid(map);
	if (error != no_errors)
		return (error);
	if (map->all_text_set == 1)
	{
		error = is_map_lines_valid(map, cub_map, cub_map_index);
		if (error != no_errors)
			return (error);
	}
	if (map->textures.east_id == 1 && map->textures.ceiling_id == 1 && \
	map->textures.floor_id == 1 && map->textures.north_id == 1 && \
	map->textures.south_id == 1 && map->textures.west_id == 1)
		map->all_text_set = 1;
	return (no_errors);
}
