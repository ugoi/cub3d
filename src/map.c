/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:24:21 by sdukic            #+#    #+#             */
/*   Updated: 2023/02/10 23:24:23 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/map.h"
#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "MLX42.h"
#include "./include/player.h"
#include "./include/colors.h"
#include "./include/my_math.h"

char	*get_next_line(int fd)
{
	char	*string;
	char	*copy;

	string = malloc(10000);
	copy = string;
	while (read(fd, copy, 1) > 0)
	{
		if (*copy == '\n')
			break ;
	copy++;
	}
	if (copy > string)
	{
		*copy = 0;
		return (string);
	}
	else
	{
		free(string);
		return (NULL);
	}
}

t_int_vector	get_map_dimesnions(char **map)
{
	int				i;
	t_int_vector	dim;

	dim.x = 0;
	dim.y = 0;
	i = 0;
	while (map[i] != NULL)
	{
		dim.y++;
		dim.x = max(dim.x, (int)strlen(map[i]));
		i++;
	}
	return (dim);
}

void	copy_to_scaled_map(char **scaled_map, char **map, int scaling_factor,
	t_int_vector dim)
{
	t_4d_vector		p;

	p.x = 0;
	while (p.x < dim.y)
	{
		p.y = 0;
		while (p.y < (int)strlen(map[p.x]))
		{
			p.z = p.x * scaling_factor;
			while (p.z < (p.x + 1) * scaling_factor)
			{
				p.w = p.y * scaling_factor;
				while (p.w < (p.y + 1) * scaling_factor)
				{
					scaled_map[p.z][p.w] = map[p.x][p.y];
					p.w++;
				}
				p.z++;
			}
			p.y++;
		}
		p.x++;
	}
}

char	**scale_map(char **map, int scaling_factor)
{
	int				i;
	char			**scaled_map;
	t_int_vector	dim;

	dim = get_map_dimesnions(map);
	scaled_map = (char **)malloc(sizeof(char *) * (dim.y * scaling_factor + 1));
	i = 0;
	while (i < dim.y * scaling_factor)
	{
		scaled_map[i] = (char *)malloc(sizeof(char)
				* (dim.x * scaling_factor + 1));
		i++;
	}
	scaled_map[dim.y * scaling_factor] = NULL;
	i = 0;
	while (i < dim.y * scaling_factor)
	{
		memset(scaled_map[i], '0', dim.x * scaling_factor);
		scaled_map[i][dim.x * scaling_factor] = '\0';
		i++;
	}
	copy_to_scaled_map(scaled_map, map, scaling_factor, dim);
	return (scaled_map);
}

float	get_fscaling_factor(t_int_vector raw_dimensions,
	t_int_vector scaled_dimensions)
{
	t_float_vector	scaling_factors;
	float			scaling_factor;

	scaling_factors.x = (float)scaled_dimensions.x / (float)raw_dimensions.x;
	scaling_factors.y = (float)scaled_dimensions.y / (float)raw_dimensions.y;
	scaling_factor = min(scaling_factors.x, scaling_factors.y);
	return (scaling_factor);
}

void	my_error(char *str)
{
	printf("ERROR: %s\n", str);
	exit(0);
}

t_int_vector	get_map_dimesnions_in_file(char *map_file)
{
	t_int_vector	dim;
	char			*line;
	int				fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		my_error("Could not open map file");
	dim.y = 0;
	dim.x = 0;
	line = get_next_line(fd);
	while (line)
	{
		dim.x = max(dim.x, (int)strlen(line));
		dim.y++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (dim);
}

char	**allocate_map_memory(t_int_vector dim)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * (dim.y + 1));
	i = 0;
	while (i < dim.y)
	{
		map[i] = malloc(sizeof(char) * (dim.x + 1));
		i++;
	}
	map[i] = NULL;
	return (map);
}

void read_map_from_file(char **map, int fd)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		j = 0;
		while (line[j] && line[j] != '\n')
		{
			map[i][j] = line[j];
			j++;
		}
		map[i][j] = 0;
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

char **init_raw_map(char *map_file)
{
	int				fd;
	char			**map;
	t_int_vector	dim;

	dim = get_map_dimesnions_in_file(map_file);
	fd = open(map_file, O_RDONLY);
	map = allocate_map_memory(dim);
	read_map_from_file(map, fd);
	close(fd);
	return (map);
}

char	**init_texture(char *texture_path)
{
	char	**texture;

	texture = init_raw_map(texture_path);
	return (texture);
}

int	draw_player(mlx_image_t *map_img, t_player *player, t_map *map)
{
	float				scaling_factor;
	int					player_size;
	int					top_left_x;
	int					top_left_y;

	scaling_factor = map->minimap_scaling_factor;
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
	return (0);
}

int	draw_map(mlx_image_t *map_img, t_map *map, t_player *player)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	while (map->mini_map[y])
	{
		while (map->mini_map[y][x])
		{
			if (map->mini_map[y][x] == '1')
				mlx_put_pixel(map_img, x, y, get_rgba(WHITE));
			else
				mlx_put_pixel(map_img, x, y, get_rgba(BLACK));
			x++;
		}
		x = 0;
		y++;
	}
	draw_player(map_img, player, map);
	return (0);
}

void	map_constructor(t_map *map)
{
	char		*map_file;

	map_file = "./maps/map1.txt";
	map->raw_map = init_raw_map(map_file);
	map->raw_map_dimensions = get_map_dimesnions(map->raw_map);
	map->south_texture.texture = init_texture("./textures/south_texture.txt");
	map->south_texture.dimensions = get_map_dimesnions(
			map->south_texture.texture);
	map->north_texture.texture = init_texture("./textures/north_texture.txt");
	map->north_texture.dimensions = get_map_dimesnions(
			map->north_texture.texture);
	map->east_texture.texture = init_texture("./textures/east_texture.txt");
	map->east_texture.dimensions = get_map_dimesnions(
			map->east_texture.texture);
	map->west_texture.texture = init_texture("./textures/west_texture.txt");
	map->west_texture.dimensions = get_map_dimesnions(
			map->west_texture.texture);
	map->minimap_dimensions = (t_int_vector){WIDTH / 4, WIDTH / 4};
	map->minimap_scaling_factor = get_fscaling_factor(
			map->raw_map_dimensions, map->minimap_dimensions);
	map->mini_map = scale_map(map->raw_map, map->minimap_scaling_factor);
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	map_destructor(t_map *map)
{
	free_2d_array(map->raw_map);
	free_2d_array(map->mini_map);
	free_2d_array(map->south_texture.texture);
	free_2d_array(map->north_texture.texture);
	free_2d_array(map->east_texture.texture);
	free_2d_array(map->west_texture.texture);
}
