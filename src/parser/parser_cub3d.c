#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../../gnl/get_next_line.h"
#include "../../../libft/libft.h"

#include "parser.h"




int	check_map(t_map_parsing *map, char **cub_map, int *cub_map_index)
{
	int	error;

	map->y = 0;
	map->all_text_set = 0;
	map->textures.east_id = 0;
	map->textures.west_id = 0;
	map->textures.north_id = 0;
	map->textures.south_id = 0;
	map->textures.floor_id = 0;
	map->textures.ceiling_id = 0;
	map->text_error = 0;

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

int	parse_map(char *cub_file)
{
	t_map_parsing map;
	static char *cub_map[MAX_ARG];
	static int cub_map_index;

	map.player_start_position = 0;
	map.fd = open(cub_file, O_RDONLY);
	if (map.fd == -1)
	{
		printf("Error\nNo such directory\n");
		close(map.fd);
		exit(EXIT_FAILURE);
	}
	if (check_map(&map, cub_map, &cub_map_index) != no_errors)
	{
		return (map_error);
	}
	if (map.player_start_position != 1)
	{
		close(map.fd);
		return (elements_error);
	}
	if (!is_top_wall_valid(map.tmp_map) || !is_bottom_wall_valid(map.tmp_map) || \
!is_right_wall_valid(map.tmp_map) || !is_left_wall_valid(map.tmp_map)
	)
	{
		close(map.fd);
		return (wall_error);
	}
	// if all is ok map can be accessed
	int	i =0;
	map.cub3d_map = cub_map;
	while (map.cub3d_map[i])
	{
		printf("%s", map.cub3d_map[i]);
		i++;
	}
	printf("%s\n",  map.textures.north_path);
	printf("%s\n",  map.textures.south_path);
	printf("%s\n", map.textures.west_path);
	printf("%s\n", map.textures.east_path);
	printf("%d, %d, %d\n", map.textures.floor1, map.textures.floor2, map.textures.floor3);
	printf("%d, %d, %d\n", map.textures.ceiling1, map.textures.ceiling2, map.textures.ceiling3);


	close(map.fd);
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
		// return (1);
		return(file_error);
	}
	return (0);
}


int main(int argc, char *argv[])
{
	int	valid_file;
	int	error;

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
	error = parse_map(argv[1]);
	if (error != 0)
	{
		printf("Error:%d:*\n", error);
	}
	// system("leaks a.out");
	return (EXIT_SUCCESS);
}
