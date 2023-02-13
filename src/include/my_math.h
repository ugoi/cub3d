/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:36:42 by sdukic            #+#    #+#             */
/*   Updated: 2023/02/13 10:46:09 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MATH_H
# define MY_MATH_H

# define DEG_TO_RAD 0.01745329251994329576923690768489
# define FOV 30.0
# define RESOLUTION 0.1
# define WIDTH 800
# define HEIGHT 600

# include "MLX42.h"

typedef struct s_int_vector
{
	int	x;
	int	y;
}				t_int_vector;

typedef struct s_4d_vector
{
	int	x;
	int	y;
	int	z;
	int	w;
}				t_4d_vector;

typedef struct s_draw_vector_params
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	int		half_width;
	int		width;
	int		color;
	int		i;
}				t_draw_vector_params;

typedef struct s_float_vector
{
	float	x;
	float	y;
}				t_float_vector;

t_int_vector	get_scaled_pos(t_float_vector pos, int scaling_factor);
float			add_radians(float radians, float radians_to_add);
int				draw_vector(mlx_image_t *img, t_int_vector start,
					t_int_vector end);
t_float_vector	add_vectors(t_float_vector v1, t_float_vector v2);

#endif
