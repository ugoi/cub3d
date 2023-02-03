/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_module.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:24:23 by stefan            #+#    #+#             */
/*   Updated: 2023/02/03 22:28:38 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_MODULE_H
# define GRAPHICS_MODULE_H

# include <stdint.h>
# include "MLX42.h"
# define PI 3.14159265358979323846
#define DEG_TO_RAD 0.01745329251994329576923690768489
#define FOV 60
#define RESOLUTION 1

typedef struct s_int_vector
{
	int	x;
	int	y;
}				t_int_vector;

typedef struct s_float_vector
{
	float	x;
	float	y;
}				t_float_vector;

typedef struct s_player
{
	t_float_vector	pos;
	t_float_vector	dir;
	float			radians;
}				t_player;

typedef struct s_map
{
	char			**raw_map;
	t_int_vector	raw_map_dimensions;
}				t_map;

typedef struct s_vars
{
	mlx_t			*mlx;
	mlx_image_t		*main_img;
	mlx_image_t		*map_img;
	t_map			*map;
	t_player		*player;
}				t_vars;

int32_t	init_window(t_map *map, t_player *player);
char	**scale_map(char **map, int scaling_factor);
int		get_scaling_factor(int width, int height, t_map *map);
float	add_radians(float radians, float radians_to_add);
t_int_vector	get_map_dimesnions(char **map);

#endif
