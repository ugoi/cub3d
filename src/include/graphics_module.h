/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_module.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:24:23 by stefan            #+#    #+#             */
/*   Updated: 2023/02/07 18:42:40 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_MODULE_H
# define GRAPHICS_MODULE_H

# include <stdint.h>
# include "MLX42.h"
#include "my_math.h"
#include "map.h"
#include "player.h"
#include "ray.h"

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
void			error(void);
int	draw_main(mlx_image_t *main_img);
void draw_columns_with_texture(mlx_image_t *img, int n, float w, int start, int end, t_ray ray, t_texture texture);

#endif
