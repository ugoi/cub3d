#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/gnl/get_next_line.h"
#include "../../lib/libft/libft.h"

#include "parser.h"

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
		{
			printf("Error:%d-\n", error);
			return (error);
		}
	}
	return (no_errors);
}

void	open_cub_fiile(t_map_parsing *map, char *cub_file)
{
	map->fd = open(cub_file, O_RDONLY);
	if (map->fd == -1)
	{
		printf("Error\nNo such directory\n");
		close(map->fd);
		exit(EXIT_FAILURE);
	}
}

int	check_player_position(t_map_parsing *map)
{
	if (map->player_start_position != 1)
	{
		close(map->fd);
		return (elements_error);
	}
	return (no_errors);
}

int	parse_map(char *cub_file, t_map_parsing *map)
{
	static char	*cub_map[MAX_ARG];
	static int	cub_map_index;

	map->player_start_position = 0;
	open_cub_fiile(map, cub_file);
	if (check_map(map, cub_map, &cub_map_index) != no_errors)
	{
		close(map->fd);
		return (map_error);
	}
	if (check_player_position(map) != no_errors)
		return (elements_error);
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
		printf("Error\nFile format not valid\n");
		return (file_error);
	}
	return (0);
}
