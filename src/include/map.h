#ifndef MAP_H
#define MAP_H

#include "my_math.h"
#define WIDTH 800
#define HEIGHT 600

typedef struct s_map
{
	char			**raw_map;
	t_int_vector	raw_map_dimensions;

	char			**mini_map;
	float			minimap_scaling_factor;
	t_int_vector	minimap_dimensions;
}				t_map;

char			*get_next_line(int fd);
char			**scale_map(char **map, int scaling_factor);
float			get_fscaling_factor(t_int_vector raw_dimensions, t_int_vector scaled_dimensions);
char			**init_raw_map(char *map_file);
t_int_vector	get_map_dimesnions(char **map);
void			map_constructor(t_map *map);
#endif