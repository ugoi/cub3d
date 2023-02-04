/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_module.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:24:23 by stefan            #+#    #+#             */
/*   Updated: 2023/02/04 22:02:50 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_MODULE_H
# define GRAPHICS_MODULE_H

# include <stdint.h>
# include "MLX42.h"
# define PI 3.14159265358979323846
#define DEG_TO_RAD 0.01745329251994329576923690768489
#define FOV 60.0
#define RESOLUTION 1
#define WIDTH 800
#define HEIGHT 600
#include "my_math.h"
#include "map.h"

typedef struct s_player
{
	t_float_vector	pos;
	t_float_vector	dir;
	float			radians;
}				t_player;

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
float	add_radians(float radians, float radians_to_add);
t_int_vector	get_map_dimesnions(char **map);

#endif
