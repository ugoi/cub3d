#ifndef MY_MATH_H
#define MY_MATH_H

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define DEG_TO_RAD 0.01745329251994329576923690768489
#define FOV 60.0
#define RESOLUTION 0.1
#define WIDTH 800
#define HEIGHT 600

#include "MLX42.h"

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

t_int_vector get_scaled_pos(t_float_vector pos, int scaling_factor);
float		add_radians(float radians, float radians_to_add);
int			draw_vector(mlx_image_t *img, t_int_vector start, t_int_vector end, int color, int width);

#endif