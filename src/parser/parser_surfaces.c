

#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../../gnl/get_next_line.h"
#include "../../../libft/libft.h"

#include "parser.h"

int	is_valid_num(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
		{
			printf("Error\nInvalid Floor or Ceiling parameter used\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	set_floor_vals(t_map_parsing *map, char **split_vals, char *tmp_floor)
{
	int	i;

	i = 0;
	while (split_vals[i])
	{
		if (!is_valid_num(split_vals[i]))
		{
			free(tmp_floor);
			ft_free(split_vals);
			return (texture_error);
		}
		i++;
	}
	map->textures.floor1 = ft_atoi(split_vals[0]);
	map->textures.floor2 = ft_atoi(split_vals[1]);
	map->textures.floor3 = ft_atoi(split_vals[2]);
	map->floor_vals_set = 1;
	if (map->textures.floor1 < 0 || map->textures.floor1 > 255 || map->textures.floor2 < 0 || map->textures.floor2 > 255 || map->textures.floor3 < 0 || map->textures.floor3 > 255)
	{
		free(tmp_floor);
		ft_free(split_vals);
		return (texture_error);
	}
	return (no_errors);
}


int	parse_map_floor(char *vals, t_map_parsing *map)
{
	char	*tmp_floor;
	char	**split_vals;
	int		error;

	tmp_floor  = ft_substr(vals, 0, ft_strlen(vals) - 1);
	split_vals = ft_split(tmp_floor, ',');
	if (!split_vals)
	{
		free(tmp_floor);
		return (map_error);
	}
	if (split_count(split_vals) != 3)
	{
		map->text_error= 1;
		free(tmp_floor);
		ft_free(split_vals);
		return (map_error);
	}
	error = set_floor_vals(map, split_vals, tmp_floor);
	if (error != no_errors)
		return (error);
	free(tmp_floor);
	ft_free(split_vals);
	return (no_errors);
}

int	set_ceiling_vals(t_map_parsing *map, char **split_vals, char *tmp_ceiling)
{
	int	i;

	i = 0;
	while (split_vals[i])
	{
		if (!is_valid_num(split_vals[i]))
		{
			free(tmp_ceiling);
			ft_free(split_vals);
			return (texture_error);
		}
		i++;
	}
	map->textures.ceiling1 = ft_atoi(split_vals[0]);
	map->textures.ceiling2 = ft_atoi(split_vals[1]);
	map->textures.ceiling3 = ft_atoi(split_vals[2]);
	map->ceiling_vals_set = 1;
	if (map->textures.ceiling1 < 0 || map->textures.ceiling1 > 255 || map->textures.ceiling2 < 0 || map->textures.ceiling2 > 255 || map->textures.ceiling3 < 0 || map->textures.ceiling3 > 255)
	{
		ft_free(split_vals);
		free(tmp_ceiling);
		return (texture_error);
	}
	return (no_errors);
}

int	parse_map_ceiling(char *vals, t_map_parsing *map)
{
	char	*tmp_ceiling;
	char	**split_vals;
	int		error;

	tmp_ceiling = ft_substr(vals, 0, ft_strlen(vals) - 1);
	split_vals = ft_split(tmp_ceiling, ',');
	if (!split_vals)
	{
		free(tmp_ceiling);
		return (map_error);
	}
	if (split_count(split_vals) != 3)
	{
		free(tmp_ceiling);
		ft_free(split_vals);
		return (map_error);
	}
	printf("Parsing ceiling:%s:\n", tmp_ceiling);
	error = set_ceiling_vals(map, split_vals, tmp_ceiling);
	if (error != no_errors)
		return (error);
	ft_free(split_vals);
	free(tmp_ceiling);
	return (no_errors);
}