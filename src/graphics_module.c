/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_module.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:10:52 by stefan            #+#    #+#             */
/*   Updated: 2023/02/01 16:16:24 by stefan           ###   ########.fr       */
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

int draw_player(mlx_image_t *map_img, t_player *player, t_map *map)
{
	t_int_vector	map_dimensions;
	int				square_width;
	int				square_height;
	int				min_square_size;
	int				player_size;
	int				top_left_x;
	int				top_left_y;

	map_dimensions = get_map_dimesnions(map->raw_map);
	square_width = map_img->width / map_dimensions.x;
	square_height = map_img->height / map_dimensions.y;
	min_square_size = square_width < square_height ? square_width : square_height;
	player_size = min_square_size / 4;
	top_left_x = player->pos.x * min_square_size;
	
	while (top_left_x < player->pos.x * min_square_size + player_size)
	{
		printf("top_left_x: %d\n", top_left_x);
		top_left_y = player->pos.y * min_square_size;
		while (top_left_y < player->pos.y * min_square_size + player_size)
		{
			printf("top_left_y: %d\n", top_left_y);
			mlx_put_pixel(map_img, top_left_x, top_left_y, get_rgba(GREEN));
			top_left_y++;
		}
		top_left_x++;
	}
	return (0);
}

// int draw_map(mlx_image_t *map_img, t_map *map, t_player *player)
// {
// 	t_int_vector	map_dimensions;
// 	int				square_width;
// 	int				square_height;
// 	int				min_square_size;

// 	(void)(player);
// 	map_dimensions = get_map_dimesnions(map->raw_map);
// 	square_width = map_img->width / map_dimensions.x;
// 	square_height = map_img->height / map_dimensions.y;
// 	min_square_size = square_width < square_height ? square_width : square_height;
	
// 	uint32_t x = 0;
// 	uint32_t y = 0;
// 	while (y < map_img->height && map->raw_map[y / min_square_size] )
// 	{
// 		while (x < map_img->width && map->raw_map[y / min_square_size][x / min_square_size])
// 		{
// 			if (map->raw_map[y / min_square_size][x / min_square_size] == '1')
// 			{
// 				mlx_put_pixel(map_img, x, y, get_rgba(WHITE));
// 			}
// 			else
// 			{
// 				mlx_put_pixel(map_img, x, y, get_rgba(BLACK));
// 			}
// 			x++;
// 		}
// 		x = 0;
// 		y++;
// 	}
// 	return (0);
// }

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

int get_scaling_factor(int width, int height, char **map)
{
	t_int_vector map_dimensions = get_map_dimesnions(map);
	t_int_vector scaling_factors;
	int scaling_factor;

	scaling_factors.x = width / map_dimensions.x;
	scaling_factors.y = height / map_dimensions.y;
	scaling_factor = min(scaling_factors.x, scaling_factors.y);
	return (scaling_factor);
}

int draw_map(mlx_image_t *map_img, t_map *map, t_player *player)
{
	int scaling_factor = get_scaling_factor(map_img->width, map_img->height, map->raw_map);
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



int32_t	init_window(t_map *map, t_player *player)
{
	t_vars		vars;

	vars.map = map;
	vars.player = player;
	vars.mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
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
	mlx_loop(vars.mlx);
	mlx_delete_image(vars.mlx, vars.map_img);
	mlx_delete_image(vars.mlx, vars.main_img);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
