#include "./include/map.h"
#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *get_next_line(int fd)
{
    char *string = malloc(10000), *copy = string;
    while (read(fd, copy, 1) > 0 && *copy++ != '\n');
    return (copy > string) ? (*copy = 0, string) : (free(string), NULL);
}

char **scale_map(char **map, int scaling_factor)
{
	int i, j, k, l;
	int rows = 0;
	int cols = 0;

	// Find the number of rows and columns in the map
	for (i = 0; map[i] != NULL; i++) {
		rows++;
		cols = max(cols, (int)strlen(map[i]));
	}

	// Allocate memory for the scaled map
	char **scaled_map = (char **)malloc(sizeof(char *) * (rows * scaling_factor + 1));
	for (i = 0; i < rows * scaling_factor; i++) {
		scaled_map[i] = (char *)malloc(sizeof(char) * (cols * scaling_factor + 1));
	}
	scaled_map[rows * scaling_factor] = NULL;

	// Initialize the scaled map
	for (i = 0; i < rows * scaling_factor; i++) {
		for (j = 0; j < cols * scaling_factor; j++) {
			scaled_map[i][j] = '0';
		}
		scaled_map[i][cols * scaling_factor] = '\0';
	}

	// Copy the values from the original map to the scaled map
	for (i = 0; i < rows; i++) {
		for (j = 0; j < (int)strlen(map[i]); j++) {
			for (k = i * scaling_factor; k < (i + 1) * scaling_factor; k++) {
				for (l = j * scaling_factor; l < (j + 1) * scaling_factor; l++) {
					scaled_map[k][l] = map[i][j];
				}
			}
		}
	}

	return scaled_map;
}

float	get_fscaling_factor(t_int_vector raw_dimensions, t_int_vector scaled_dimensions)
{
	t_float_vector scaling_factors;
	float scaling_factor;

	scaling_factors.x = (float)scaled_dimensions.x / (float)raw_dimensions.x;
	scaling_factors.y = (float)scaled_dimensions.y / (float)raw_dimensions.y;
	scaling_factor = min(scaling_factors.x, scaling_factors.y);
	return (scaling_factor);
}

char	**init_raw_map(char *map_file)
{
	char	**map;
	int		fd;
	int		i;
	int		j;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening map file %s\n", map_file);
		exit(1);
	}
	i = 0;
	while (get_next_line(fd))
	{
		i++;
	}
	close(fd);
	fd = open(map_file, O_RDONLY);
	map = malloc(sizeof(char *) * (i + 1));
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		j = 0;
		map[i] = malloc(sizeof(char) * 10);
		while (line[j] && line[j] != '\n')
		{
			map[i][j] = line[j];
			j++;
		}
		map[i][j] = 0;
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

t_int_vector	get_map_dimesnions(char **map)
{
	t_int_vector	map_dimensions;
	int				max_x;

	map_dimensions.x = 0;
	map_dimensions.y = 0;
	while (map[map_dimensions.y])
	{
		max_x = 0;
		while (map[map_dimensions.y][max_x])
		{
			max_x++;
		}
		if (max_x > map_dimensions.x)
			map_dimensions.x = max_x;
		map_dimensions.y++;
	}
	return (map_dimensions);
}

void map_constructor(t_map *map)
{
	char		*map_file;
	
	map_file = "./maps/map1.txt";
	map->raw_map = init_raw_map(map_file);
	map->raw_map_dimensions = get_map_dimesnions(map->raw_map);
	map->minimap_dimensions = (t_int_vector){WIDTH / 4, WIDTH / 4};
	map->minimap_scaling_factor = get_fscaling_factor(map->raw_map_dimensions, map->minimap_dimensions);
	map->mini_map = scale_map(map->raw_map, map->minimap_scaling_factor);
}