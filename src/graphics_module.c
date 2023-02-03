/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_module.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:10:52 by stefan            #+#    #+#             */
/*   Updated: 2023/02/04 00:05:44 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_module.h"
#include "graphics_module.h"
#include "./include/colors.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include "MLX42.h"
#define WIDTH 800
#define HEIGHT 600
#include <math.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

static void	error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
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

int draw_vector(mlx_image_t *img, t_int_vector start, t_int_vector end, int color)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;

	x = start.x;
	y = start.y;
	dx = abs(end.x - start.x);
	dy = abs(end.y - start.y);
	sx = start.x < end.x ? 1 : -1;
	sy = start.y < end.y ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		mlx_put_pixel(img, x, y, color);
		if (x == end.x && y == end.y)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y += sy;
		}
	}
	return (0);
}

int draw_vector2(mlx_image_t *img, t_int_vector start, t_int_vector end, int color, int width)
{
    int		x;
    int		y;
    int		dx;
    int		dy;
    int		sx;
    int		sy;
    int		err;
    int		e2;
    int     half_width;

    half_width = width / 2;

    x = start.x;
    y = start.y;
    dx = abs(end.x - start.x);
    dy = abs(end.y - start.y);
    sx = start.x < end.x ? 1 : -1;
    sy = start.y < end.y ? 1 : -1;
    err = (dx > dy ? dx : -dy) / 2;
    while (1)
    {
        for (int i = -half_width; i <= half_width; i++)
            mlx_put_pixel(img, x + i, y, color);
        if (x == end.x && y == end.y)
            break ;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y += sy;
        }
    }
    return (0);
}




int get_scaling_factor(int width, int height, t_map *map)
{
	t_int_vector map_dimensions = map->raw_map_dimensions;
	t_int_vector scaling_factors;
	int scaling_factor;

	scaling_factors.x = width / map_dimensions.x;
	scaling_factors.y = height / map_dimensions.y;
	scaling_factor = min(scaling_factors.x, scaling_factors.y);
	return (scaling_factor);
}

t_int_vector get_scaled_player_pos(t_float_vector pos, int scaling_factor)
{
	t_int_vector scaled_player_pos;

	scaled_player_pos.x = pos.x * scaling_factor;
	scaled_player_pos.y = pos.y * scaling_factor;
	return (scaled_player_pos);
}

int draw_player(mlx_image_t *map_img, t_player *player, t_map *map)
{
	int				scaling_factor;
	int				player_size;
	int				top_left_x;
	int				top_left_y;
	t_int_vector	scaled_player_pos;

	scaling_factor = get_scaling_factor(map_img->width, map_img->height, map);
	scaled_player_pos = get_scaled_player_pos(player->pos, scaling_factor);
	player_size = scaling_factor / 4;
	top_left_x = player->pos.x * scaling_factor;
	while (top_left_x < player->pos.x * scaling_factor + player_size)
	{
		top_left_y = player->pos.y * scaling_factor;
		while (top_left_y < player->pos.y * scaling_factor + player_size)
		{
			mlx_put_pixel(map_img, top_left_x, top_left_y, get_rgba(GREEN));
			top_left_y++;
		}
		top_left_x++;
	}
	draw_vector2(map_img, scaled_player_pos, (t_int_vector){scaled_player_pos.x + cos(player->radians) * map_img->width / 8, scaled_player_pos.y + sin(player->radians) * map_img->width / 8}, get_rgba(RED), 2);
	return (0);
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

int draw_map(mlx_image_t *map_img, t_map *map, t_player *player)
{
	int scaling_factor = get_scaling_factor(map_img->width, map_img->height, map);
	char **scaled_map = scale_map(map->raw_map, scaling_factor);
	(void)(player);

	uint32_t x = 0;
	uint32_t y = 0;
	while (scaled_map[y])
	{
		while (scaled_map[y][x])
		{
			if (scaled_map[y][x] == '1')
			{
				mlx_put_pixel(map_img, x, y, get_rgba(WHITE));
			}
			else
			{
				mlx_put_pixel(map_img, x, y, get_rgba(BLACK));
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int	draw_main(mlx_image_t *main_img)
{
	uint32_t x = 0;
	uint32_t y = 0;
	while (y < main_img->height)
	{
		while (x < main_img->width)
		{
			mlx_put_pixel(main_img, x, y, get_rgba(RED));
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

void	resize_func(int32_t width, int32_t height, void* data)
{
	t_vars* vars;

	vars = (t_vars*)data;
	mlx_delete_image(vars->mlx, vars->main_img);
	vars->main_img = mlx_new_image(vars->mlx, width, height);
	draw_main(vars->main_img);
	mlx_image_to_window(vars->mlx, vars->main_img, 0, 0);
	mlx_delete_image(vars->mlx, vars->map_img);
	vars->map_img = mlx_new_image(vars->mlx, width / 4, width / 4);
	draw_map(vars->map_img, vars->map, vars->player);
	mlx_image_to_window(vars->mlx, vars->map_img, 0, 0);
}

void normalize_vector(t_float_vector *vector)
{
	float length = sqrtf(vector->x * vector->x + vector->y * vector->y);
	vector->x /= length;
	vector->y /= length;
}

void set_vector(t_float_vector *vector, t_float_vector new_vector)
{
	vector->x = new_vector.x;
	vector->y = new_vector.y;
}

float	add_radians(float radians, float radians_to_add)
{
	radians += radians_to_add;
	if (radians > 2 * M_PI)
		radians -= 2 * M_PI;
	else if (radians < 0)
		radians += 2 * M_PI;
	return (radians);
}

void draw_line(mlx_image_t *img, t_int_vector start, t_int_vector end, uint32_t color)
{
	int32_t dx = abs(end.x - start.x);
	int32_t sx = start.x < end.x ? 1 : -1;
	int32_t dy = -abs(end.y - start.y);
	int32_t sy = start.y < end.y ? 1 : -1;
	int32_t err = dx + dy;
	int32_t e2;

	while (1)
	{
		mlx_put_pixel(img, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			start.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			start.y += sy;
		}
	}
}

void raycast3D(t_vars *vars)
{
	int i;
	float ray_angle;
	t_float_vector ray_pos;
	int scaling_factor;
	t_int_vector scaled_player_pos;
	t_float_vector offset;
	int		dof;
	t_int_vector ray_pos_in_map;

	float vertical_distance;
	float horizontal_distance;
	float vertical_ray_pos_x;
	float vertical_ray_pos_y;
	float shortest_distance;


	scaling_factor = get_scaling_factor(vars->map_img->width, vars->main_img->height, vars->map);
	scaled_player_pos = get_scaled_player_pos(vars->player->pos, scaling_factor);

	ray_angle = add_radians(vars->player->radians, -FOV/2 * DEG_TO_RAD);
	i = 0;
	printf("\nPlayer pos: %f, %f\n", vars->player->pos.x, vars->player->pos.y);
	draw_main(vars->main_img);
	while (i < FOV / RESOLUTION)
	{
		horizontal_distance = 0;
		vertical_distance = 0;
		shortest_distance = 0;
		ray_angle = add_radians(ray_angle, DEG_TO_RAD * RESOLUTION);

		//Check horizontal lines
		dof = 0;
		if (ray_angle < M_PI)
		{
			ray_pos.y = ceilf(vars->player->pos.y);
			ray_pos.x = vars->player->pos.x + (ray_pos.y - vars->player->pos.y) / tanf(ray_angle);
			offset.y = 1;
			offset.x = offset.y / tanf(ray_angle);
		}
		else
		{
			ray_pos.y = floorf(vars->player->pos.y);
			ray_pos.x = vars->player->pos.x + (ray_pos.y - vars->player->pos.y) / tanf(ray_angle);
			offset.y = -1;
			offset.x = offset.y / tanf(ray_angle);
		}
		if (ray_angle == 0 || ray_angle == M_PI)
		{
			// ray_pos.x = vars->player->pos.x;
			// ray_pos.y = vars->player->pos.y;
			set_vector(&ray_pos, vars->player->pos);
			offset.x = 0;
			offset.y = 0;
		}

		while (dof < 8)
		{
			if (offset.y < 0)
				ray_pos_in_map.y = (int)ray_pos.y - 1;
			else
				ray_pos_in_map.y = (int)ray_pos.y;
			ray_pos_in_map.x = (int)ray_pos.x;
			if (ray_pos_in_map.x < vars->map->raw_map_dimensions.x && ray_pos_in_map.x >= 0 && ray_pos_in_map.y < vars->map->raw_map_dimensions.y && ray_pos_in_map.y >= 0 && vars->map->raw_map[ray_pos_in_map.y][ray_pos_in_map.x] == '1')
			{
				// printf("Horizontal intersection at (%f, %f)\n", ray_pos.x, ray_pos.y);
				horizontal_distance = hypotf(vars->player->pos.x - ray_pos.x, vars->player->pos.y - ray_pos.y);
				break;
			}
			else
			{
				ray_pos.x += offset.x;
				ray_pos.y += offset.y;
			}
			dof++;
		}

		//Check vertical lines
		dof = 0;
		if (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2)
		{
			vertical_ray_pos_x = ceilf(vars->player->pos.x);
			vertical_ray_pos_y = vars->player->pos.y + (vertical_ray_pos_x - vars->player->pos.x) * tanf(ray_angle);
			offset.x = 1;
			offset.y = offset.x * tanf(ray_angle);
		}
		else
		{
			vertical_ray_pos_x = floorf(vars->player->pos.x);
			vertical_ray_pos_y = vars->player->pos.y + (vertical_ray_pos_x - vars->player->pos.x) * tanf(ray_angle);
			offset.x = -1;
			offset.y = offset.x * tanf(ray_angle);
		}
		if (ray_angle == M_PI / 2 || ray_angle == 3 * M_PI / 2)
		{
			vertical_ray_pos_x = vars->player->pos.x;
			vertical_ray_pos_y = vars->player->pos.y;
			offset.x = 0;
			offset.y = 0;
		}

		while (dof < 8)
		{
			if (offset.x < 0)
				ray_pos_in_map.x = (int)vertical_ray_pos_x - 1;
			else
				ray_pos_in_map.x = (int)vertical_ray_pos_x;
			ray_pos_in_map.y = (int)vertical_ray_pos_y;
			if (ray_pos_in_map.x < vars->map->raw_map_dimensions.x && ray_pos_in_map.y >= 0 && ray_pos_in_map.y < vars->map->raw_map_dimensions.y && ray_pos_in_map.x >= 0 && vars->map->raw_map[ray_pos_in_map.y][ray_pos_in_map.x] == '1')
			{
				// printf("Vertical intersection at (%f, %f)\n", vertical_ray_pos_x, vertical_ray_pos_y);
				vertical_distance = hypotf(vars->player->pos.x - vertical_ray_pos_x, vars->player->pos.y - vertical_ray_pos_y);
				break;
			}
			else
			{
				vertical_ray_pos_x += offset.x;
				vertical_ray_pos_y += offset.y;
			}
			dof++;
		}

		// printf("Horizonstal ray pos: %f,%f  Vertical ray pos: %f, %f\n", ray_pos.x, ray_pos.y, vertical_ray_pos_x, vertical_ray_pos_y);
		if ((horizontal_distance <= vertical_distance || vertical_distance <= 0) && horizontal_distance > 0)
		{
			// ray_pos.x = ray_pos.x;
			// ray_pos.y = ray_pos.y;
			shortest_distance = horizontal_distance;
		}
		else
		{
			ray_pos.x = vertical_ray_pos_x;
			ray_pos.y = vertical_ray_pos_y;
			shortest_distance = vertical_distance;
		}
		// printf("Ray%d pos: (%f, %f) angle: %f\n", i, ray_pos.x, ray_pos.y, ray_angle);
		// if (ray_pos.x < vars->map->raw_map_dimensions.x && ray_pos.y < vars->map->raw_map_dimensions.y && ray_pos.x >= 0 && ray_pos.y >= 0)
		// 	{
		// 	printf("Ray%d pos: (%f, %f) angle: %f\n", i, ray_pos.x, ray_pos.y, ray_angle);


		// 	}
		draw_vector(vars->map_img, scaled_player_pos, get_scaled_player_pos(ray_pos, scaling_factor), get_rgba(BLUE));

		//Draw 3D walls
		float ca=add_radians(vars->player->radians, -ray_angle); shortest_distance=shortest_distance*cos(ca);                            //fix fisheye
		float line_height = 100 / shortest_distance;
		float block_width = vars->main_img->width / (FOV / RESOLUTION);
		int line_start = vars->main_img->height / 2 - line_height / 2;
		int line_end = vars->main_img->height / 2 + line_height / 2;
		if (line_start < 0)
			line_start = 0;
		if (line_end > (int)vars->main_img->height)
			line_end = (int)vars->main_img->height;
		draw_line(vars->main_img, (t_int_vector){i * (block_width), line_start}, (t_int_vector){i * (block_width), line_end}, get_rgba(WHITE));
		// draw_vector2(vars->main_img, (t_int_vector){i * block_width + block_width / 2, line_start}, (t_int_vector){i * block_width + block_width / 2, line_end}, get_rgba(WHITE), block_width);


		i++;
	}
}


void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_vars *vars;

	vars = (t_vars*)param;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		vars->player->pos.x += 0.1 * cos(vars->player->radians);
		vars->player->pos.y += 0.1 * sin(vars->player->radians);
		draw_map(vars->map_img, vars->map, vars->player);
		draw_player(vars->map_img, vars->player, vars->map);
		raycast3D(vars);
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		vars->player->pos.x -= 0.1 * cos(vars->player->radians);
		vars->player->pos.y -= 0.1 * sin(vars->player->radians);
		draw_map(vars->map_img, vars->map, vars->player);
		draw_player(vars->map_img, vars->player, vars->map);
		raycast3D(vars);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		vars->player->pos.x -= 0.1 * cos(vars->player->radians + M_PI / 2);
		vars->player->pos.y -= 0.1 * sin(vars->player->radians + M_PI / 2);
		draw_map(vars->map_img, vars->map, vars->player);
		draw_player(vars->map_img, vars->player, vars->map);
		raycast3D(vars);
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		vars->player->pos.x += 0.1 * cos(vars->player->radians + M_PI / 2);
		vars->player->pos.y += 0.1 * sin(vars->player->radians + M_PI / 2);
		draw_map(vars->map_img, vars->map, vars->player);
		draw_player(vars->map_img, vars->player, vars->map);
		raycast3D(vars);
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		vars->player->radians = add_radians(vars->player->radians, -0.1);
		// printf("Player angle: %f\n", vars->player->radians);
		draw_map(vars->map_img, vars->map, vars->player);
		draw_player(vars->map_img, vars->player, vars->map);
		raycast3D(vars);
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		vars->player->radians = add_radians(vars->player->radians, 0.1);
		// printf("Player angle: %f\n", vars->player->radians);
		draw_map(vars->map_img, vars->map, vars->player);
		draw_player(vars->map_img, vars->player, vars->map);
		raycast3D(vars);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		exit(0);
	}
}

int32_t	init_window(t_map *map, t_player *player)
{
	t_vars		vars;

	vars.map = map;
	vars.player = player;
	vars.mlx = mlx_init(WIDTH, HEIGHT, "Test", false);
	if (!vars.mlx)
		error();
	vars.main_img = mlx_new_image(vars.mlx, vars.mlx->width, vars.mlx->height);
	if (!vars.main_img)
		error();
	draw_main(vars.main_img);
	if (mlx_image_to_window(vars.mlx, vars.main_img, 0, 0) < 0)
		error();
	vars.map_img = mlx_new_image(vars.mlx, WIDTH / 4, WIDTH / 4);
	if (!vars.map_img)
		error();
	draw_map(vars.map_img, map, player);
	draw_player(vars.map_img, player, map);
	if (mlx_image_to_window(vars.mlx, vars.map_img, 0, 0) < 0)
		error();
	mlx_resize_hook(vars.mlx, resize_func, &vars);
	mlx_key_hook(vars.mlx, my_keyhook, &vars);
	mlx_loop(vars.mlx);
	mlx_delete_image(vars.mlx, vars.map_img);
	mlx_delete_image(vars.mlx, vars.main_img);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
