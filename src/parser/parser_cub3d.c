/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cub3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:50:27 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/13 22:24:05 by bogunlan         ###   ########.fr       */
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

void	open_cub_fiile(t_map_parsing *map, char *cub_file)
{
	map->fd = open(cub_file, O_RDONLY);
	if (map->fd == -1)
	{
		cub3d_error_messg(file_error, NULL);
		close(map->fd);
		exit(EXIT_FAILURE);
	}
}

int	check_player_position(t_map_parsing *map)
{
	if (map->player_start_position != 1)
	{
		close(map->fd);
		return (map_error);
	}
	return (no_errors);
}

int	map_has_nl_at_end(char **cub3d_map)
{
	int	i;

	i = 0;
	while (cub3d_map[i])
		i++;
	if (ft_strchr(cub3d_map[i - 1], '\n'))
		return (TRUE);
	return (FALSE);
}

int	check_wall_sides(t_map_parsing *map)
{
	if (!is_top_wall_valid(map->tmp_map) || \
!is_bottom_wall_valid(map->tmp_map) || \
!is_right_wall_valid(map->tmp_map) || !is_left_wall_valid(map->tmp_map)
	)
	{
		close(map->fd);
		return (wall_error);
	}
	return (no_errors);
}

int	parse_map(char *cub_file, t_map_parsing *map)
{
	static char	*cub_map[MAX_ARG];
	static int	cub_map_index;
	int			error;

	map->player_start_position = 0;
	map->cub3d_map = cub_map;
	open_cub_fiile(map, cub_file);
	error = check_map(map, cub_map, &cub_map_index);
	if (error)
	{
		close(map->fd);
		return (error);
	}
	if (check_player_position(map) != no_errors)
		return (map_error);
	if (check_wall_sides(map) != no_errors)
		return (map_error);
	close(map->fd);
	if (map_has_nl_at_end(map->cub3d_map))
		return (map_error);
	return (0);
}
