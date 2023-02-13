/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_module.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:24:23 by stefan            #+#    #+#             */
/*   Updated: 2023/02/13 00:28:21 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_MODULE_H
# define GRAPHICS_MODULE_H

# include <stdint.h>
# include "MLX42.h"
# include "my_math.h"
# include "map.h"
# include "player.h"
# include "ray.h"

typedef struct s_vars
{
	mlx_t			*mlx;
	mlx_image_t		*main_img;
	mlx_image_t		*map_img;
	t_map			*map;
	t_player		*player;
}				t_vars;

typedef struct s_texdim
{
	int				n;
	float			w;
	int				start;
	int				end;
}				t_texdim;

int32_t			init_window(t_map *map, t_player *player);
char			**scale_map(char **map, int scaling_factor);
float			add_radians(float radians, float radians_to_add);
t_int_vector	get_map_dimesnions(char **map);
void			error(void);
int				draw_main(mlx_image_t *main_img, int floor_color,
					int ceiling_color);
void			draw_columns_with_texture(mlx_image_t *img, t_texdim d,
					t_ray ray, t_texture texture);
t_int_vector	calculate_texture( t_ray ray, t_texture texture,
					float ty_ratio);
uint32_t		get_color_from_texture(t_texture texture,
					t_int_vector texture_iter);
void			draw_3d_walls(t_vars *vars, t_ray shortest_ray, int i,
					t_texture texture);
void			raycast3d(t_vars *vars);
void			my_keyhook(mlx_key_data_t keydata, void *param);
void			my_mlx_close(void *param);
enum			e_ray_type	get_ray_type(t_ray ray);
bool			is_vertical(enum e_ray_type type);
t_int_vector	calculate_texture( t_ray ray, t_texture texture,
					float ty_ratio);
uint32_t		get_color_from_texture(t_texture texture,
					t_int_vector texture_iter);
t_texture		get_ray_texture(t_ray ray, t_map map);
t_ray			calculate_first_horizontal_ray(t_vars *vars, float angle);
t_ray			calculate_first_vertical_ray(t_vars *vars, float angle);
t_float_vector	calculate_horizontal_ray_dest(t_vars *vars, t_ray ray);
t_float_vector	calculate_vertical_ray_dest(t_vars *vars, t_ray ray);
int				draw_player(mlx_image_t *map_img, t_player *player, t_map *map);
int				draw_map(mlx_image_t *map_img, t_map *map, t_player *player);

#endif
