/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_module.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:10:52 by stefan            #+#    #+#             */
/*   Updated: 2023/02/01 22:44:24 by stefan           ###   ########.fr       */
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

int draw_player(mlx_image_t *map_img, t_player *player, t_map *map)
{
	int				scaling_factor;
	int				player_size;
	int				top_left_x;
	int				top_left_y;
	t_int_vector	scaled_player_pos;

	scaling_factor = get_scaling_factor(map_img->width, map_img->height, map);
	scaled_player_pos.x = player->pos.x * scaling_factor;
	scaled_player_pos.y = player->pos.y * scaling_factor;
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
	draw_vector(map_img, scaled_player_pos, (t_int_vector){scaled_player_pos.x + cos(player->radians) * map_img->width / 8, scaled_player_pos.y + sin(player->radians) * map_img->width / 8}, get_rgba(RED));
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

void raycast3D(t_vars *vars)
{
	t_float_vector ray_pos;

	
	//Check horizontal lines
	ray_pos.x = vars->player->pos.x;
	ray_pos.y = vars->player->pos.y;
	if (vars->player->radians > M_PI)
		ray_pos.y = floorf(ray_pos.y);
	else
		ray_pos.y = ceilf(ray_pos.y);
	ray_pos.x = ray_pos.x + (ray_pos.y - vars->player->pos.y) / tanf(vars->player->radians);
	while (ray_pos.x >= 0 && ray_pos.x < vars->map->raw_map_dimensions.x && ray_pos.y >= 0 && ray_pos.y < vars->map->raw_map_dimensions.y)
	{
		if (vars->map->raw_map[(int)ray_pos.y][(int)ray_pos.x] == '1')
		{
			printf("HORIZONTAL HIT: %f, %f\n", ray_pos.x, ray_pos.y);
			break;
		}
		ray_pos.x += 1 / tanf(vars->player->radians);
		if (vars->player->radians > M_PI)
			ray_pos.y -= 1;
		else
			ray_pos.y += 1;
	}
	
	//Check vertical lines
	ray_pos.x = vars->player->pos.x;
	ray_pos.y = vars->player->pos.y;
	if (vars->player->radians > M_PI / 2 && vars->player->radians < 3 * M_PI / 2)
		ray_pos.x = floorf(ray_pos.x);
	else
		ray_pos.x = ceilf(ray_pos.x);
	ray_pos.y = ray_pos.y + (ray_pos.x - vars->player->pos.x) * tanf(vars->player->radians);
	while (ray_pos.x >= 0 && ray_pos.x < vars->map->raw_map_dimensions.x && ray_pos.y >= 0 && ray_pos.y < vars->map->raw_map_dimensions.y)
	{
		if (vars->map->raw_map[(int)ray_pos.y][(int)ray_pos.x] == '1')
		{
			printf("VERTICAL HIT: %f, %f\n", ray_pos.x, ray_pos.y);
			break;
		}
		ray_pos.y += tanf(vars->player->radians);
		if (vars->player->radians > M_PI / 2 && vars->player->radians < 3 * M_PI / 2)
			ray_pos.x -= 1;
		else
			ray_pos.x += 1;
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
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		vars->player->pos.x -= 0.1 * cos(vars->player->radians);
		vars->player->pos.y -= 0.1 * sin(vars->player->radians);
		draw_map(vars->map_img, vars->map, vars->player);
		draw_player(vars->map_img, vars->player, vars->map);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		vars->player->pos.x -= 0.1 * cos(vars->player->radians + M_PI / 2);
		vars->player->pos.y -= 0.1 * sin(vars->player->radians + M_PI / 2);
		draw_map(vars->map_img, vars->map, vars->player);
		draw_player(vars->map_img, vars->player, vars->map);
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		vars->player->pos.x += 0.1 * cos(vars->player->radians + M_PI / 2);
		vars->player->pos.y += 0.1 * sin(vars->player->radians + M_PI / 2);
		draw_map(vars->map_img, vars->map, vars->player);
		draw_player(vars->map_img, vars->player, vars->map);
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		vars->player->radians -= 0.1;
		draw_map(vars->map_img, vars->map, vars->player);
		draw_player(vars->map_img, vars->player, vars->map);
		raycast3D(vars);
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		vars->player->radians += 0.1;
		draw_map(vars->map_img, vars->map, vars->player);
		draw_player(vars->map_img, vars->player, vars->map);
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
