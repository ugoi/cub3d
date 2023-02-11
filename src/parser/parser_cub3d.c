#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../../gnl/get_next_line.h"
#include "../../../libft/libft.h"

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
	static char *cub_map[MAX_ARG];
	static int cub_map_index;

	map->player_start_position = 0;
	open_cub_fiile(map, cub_file);
	if (check_map(map, cub_map, &cub_map_index) != no_errors)
	{
		close(map->fd);
		return (map_error);
	}
	if (check_player_position(map) != no_errors)
		return (elements_error);
	if (!is_top_wall_valid(map->tmp_map) || !is_bottom_wall_valid(map->tmp_map) || \
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
		return(file_error);
	}
	return (0);
}

// int	is_wall_texture_valid(t_map_parsing *map)
// {
// 	int	i;

// 	i = 0;
// 	while ()
// }

int main(int argc, char *argv[])
{
	int	valid_file;
	int	error;
	t_map_parsing map;

	if (argc != 2)
	{
		printf("Error\nUsage sample: ./cub3d \"./maps/map01.cub\"\n");
		return (EXIT_FAILURE);
	}
	valid_file = is_file_valid(argv);
	if (valid_file != 0)
	{
		return (EXIT_FAILURE);
	}
	error = parse_map(argv[1], &map);
	if (error != 0)
	{
		printf("Error:%d:*\n", error);
		return (EXIT_FAILURE);
	}
	printf("%s\n", map.textures.east_path);
	printf("%s\n", map.textures.north_path);
	printf("%s\n", map.textures.west_path);
	printf("%s\n", map.textures.south_path);
	// Do a check for TEXTURE path if it is valid  !+++===========================IMPORTANT=========================+++++!
	is_wall_texture_valid(&map);
	printf("%d, %d, %d\n", map.textures.ceiling1, map.textures.ceiling2, map.textures.ceiling3);
	printf("%d, %d, %d\n", map.textures.floor1, map.textures.floor2, map.textures.floor3);
	while (*map.cub3d_map)
	{
		printf("%s", *map.cub3d_map);
		map.cub3d_map++;
	}
	// system("leaks a.out");
	return (EXIT_SUCCESS);
}
