/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:35:03 by sdukic            #+#    #+#             */
/*   Updated: 2023/02/13 00:32:40 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "my_math.h"
# include "map.h"
# include "MLX42.h"
# include "./parser.h"

typedef struct s_texture
{
	char			**texture;
	t_int_vector	dimensions;
}				t_texture;

typedef struct s_map
{
	char			**raw_map;
	t_int_vector	raw_map_dimensions;

	char			**mini_map;
	float			minimap_scaling_factor;
	t_int_vector	minimap_dimensions;

	t_texture		south_texture;
	t_texture		north_texture;
	t_texture		east_texture;
	t_texture		west_texture;
	int				floor_color;
	int				ceiling_color;
}				t_map;

char			*get_next_line(int fd);
char			**scale_map(char **map, int scaling_factor);
float			get_fscaling_factor(t_int_vector raw_dimensions,
					t_int_vector scaled_dimensions);
char			**init_texture(char *map_file);
t_int_vector	get_map_dimesnions(char **map);
void			map_constructor(t_map *map, t_map_parsing *map_parsing);
char			**init_texture(char *texture_path);
void			map_destructor(t_map *map);
t_int_vector	get_texture_dim_in_file(char *map_file);
char			**allocate_map_memory(t_int_vector dim);
void			read_texture_from_file(char **map, int fd);
char			**init_texture(char *map_file);
char			**remove_newlines(char **map);
void			parser_cleaner(t_map_parsing *parser);
#endif
