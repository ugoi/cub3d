/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cub3d_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:50:09 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/12 22:37:34 by bogunlan         ###   ########.fr       */
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

void	init_map_params(t_map_parsing *map)
{
	map->y = 0;
	map->all_text_set = 0;
	map->textures.east_id = 0;
	map->textures.west_id = 0;
	map->textures.north_id = 0;
	map->textures.south_id = 0;
	map->textures.floor_id = 0;
	map->textures.ceiling_id = 0;
	map->text_error = 0;
	map->at_wall = 0;
}

int	check_map(t_map_parsing *map, char **cub_map, int *cub_map_index)
{
	int	error;

	init_map_params(map);
	while (1)
	{
		map->x = 0;
		map->line = get_next_line(map->fd);
		if (!map->line)
			return (no_errors);
		error = check_line(map, cub_map, cub_map_index);
		free(map->line);
		if (error)
			return (error);
	}
	cub_map[*cub_map_index] = NULL;
	return (no_errors);
}
