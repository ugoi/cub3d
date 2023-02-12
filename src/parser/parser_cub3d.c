/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cub3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:50:27 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/12 21:50:30 by bogunlan         ###   ########.fr       */
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

int	parse_map(char *cub_file, t_map_parsing *map)
{
	static char	*cub_map[MAX_ARG];
	static int	cub_map_index;
	int			error;

	map->player_start_position = 0;
	open_cub_fiile(map, cub_file);
	error = check_map(map, cub_map, &cub_map_index);
	if (error)
	{
		close(map->fd);
		return (error);
	}
	if (check_player_position(map) != no_errors)
		return (map_error);
	if (!is_top_wall_valid(map->tmp_map) || \
!is_bottom_wall_valid(map->tmp_map) || \
!is_right_wall_valid(map->tmp_map) || !is_left_wall_valid(map->tmp_map)
	)
	{
		close(map->fd);
		return (wall_error);
	}
	map->cub3d_map = cub_map;
	close(map->fd);
	return (0);
}

int	is_file_valid(char *argv[])
{
	t_params	params;

	params.i = 0;
	params.valid_file = 0;
	while (argv[1][params.i] != '\0')
	{
		if (argv[1][params.i] == '.')
		{
			if (argv[1][params.i + 1] == 'c' && argv[1][params.i + 2] == 'u'
			&& argv[1][params.i + 3] == 'b')
			{
				if (argv[1][params.i + 4] != '\0')
					break ;
				params.valid_file = 1;
			}
		}
		params.i++;
	}
	if (!params.valid_file)
	{
		cub3d_error_messg(file_error, NULL);
		return (file_error);
	}
	return (0);
}
