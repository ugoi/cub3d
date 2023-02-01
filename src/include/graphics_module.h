/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_module.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:24:23 by stefan            #+#    #+#             */
/*   Updated: 2023/02/01 02:52:31 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_MODULE_H
# define GRAPHICS_MODULE_H

# include <stdint.h>
# include "MLX42.h"

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
}				t_player;

typedef struct s_map
{
	char	**raw_map;
	char	**mini_map;
	char	**big_map;
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
int		get_scaling_factor(int width, int height, char **map);

#endif