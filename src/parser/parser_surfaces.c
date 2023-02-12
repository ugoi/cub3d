#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/gnl/get_next_line.h"
#include "../../lib/libft/libft.h"
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

int	set_floor_vals(t_map_parsing *map, char **split_vals)
{
	int	i;
	int	error;

	i = 0;
	error = no_errors;
	while (split_vals[i] && error == no_errors)
	{
		if (!is_valid_num(split_vals[i]))
			error = elements_error;
		i++;
	}
	map->textures.floor1 = ft_atoi(split_vals[0]);
	map->textures.floor2 = ft_atoi(split_vals[1]);
	map->textures.floor3 = ft_atoi(split_vals[2]);
	map->floor_vals_set = 1;
	if (map->textures.floor1 < 0 || map->textures.floor1 > 255 || \
	map->textures.floor2 < 0 || map->textures.floor2 > 255 || \
	map->textures.floor3 < 0 || map->textures.floor3 > 255)
		error = elements_error;
	if (error != no_errors)
		return (error);
	return (no_errors);
}

int	check_comma_separator(char *surface)
{
	if (comma_separator_is_valid(surface) != TRUE)
	{
		free(surface);
		return (elements_error);
	}
	return (no_errors);
}

int	parse_map_floor(char *vals, t_map_parsing *map)
{
	char	*tmp_floor;
	char	**split_vals;
	int		error;

	tmp_floor = ft_substr(vals, 0, ft_strlen(vals) - 1);
	if (check_comma_separator(tmp_floor) != no_errors)
		return (elements_error);
	split_vals = ft_split(tmp_floor, ',');
	if (!split_vals)
	{
		free(tmp_floor);
		return (elements_error);
	}
	if (split_count(split_vals) != 3)
		error = elements_error;
	error = set_floor_vals(map, split_vals);
	if (error != no_errors)
		error = elements_error;
	free(tmp_floor);
	ft_free(split_vals);
	if (error)
		return (error);
	return (no_errors);
}

int	set_ceiling_vals(t_map_parsing *map, char **split_vals)
{
	int	i;
	int	error;

	i = 0;
	error = no_errors;
	while (split_vals[i] && error == no_errors)
	{
		if (!is_valid_num(split_vals[i]))
			error = elements_error;
		i++;
	}
	map->textures.ceiling1 = ft_atoi(split_vals[0]);
	map->textures.ceiling2 = ft_atoi(split_vals[1]);
	map->textures.ceiling3 = ft_atoi(split_vals[2]);
	map->ceiling_vals_set = 1;
	if (map->textures.ceiling1 < 0 || map->textures.ceiling1 > 255 || \
	map->textures.ceiling2 < 0 || map->textures.ceiling2 > 255 || \
	map->textures.ceiling3 < 0 || map->textures.ceiling3 > 255)
		error = elements_error;
	if (error != no_errors)
		return (error);
	return (no_errors);
}

int	comma_separator_is_valid(char *texture_vals)
{
	int	i;

	i = 0;
	if (texture_vals[0] == ',')
		return (FALSE);
	printf(":%s:\n", texture_vals);
	while (texture_vals[i])
	{
		if (texture_vals[i] == ',')
		{
			if (texture_vals[i + 1])
			{
				if (texture_vals[i + 1] == ',')
					return (FALSE);
			}
		}
		i++;
	}
	if (texture_vals[ft_strlen(texture_vals) - 1] == ',')
		return (FALSE);
	return (TRUE);
}

int	parse_map_ceiling(char *vals, t_map_parsing *map)
{
	char	*tmp_ceiling;
	char	**split_vals;
	int		error;

	tmp_ceiling = ft_substr(vals, 0, ft_strlen(vals) - 1);
	if (check_comma_separator(tmp_ceiling) != no_errors)
		return (elements_error);
	split_vals = ft_split(tmp_ceiling, ',');
	if (!split_vals)
	{
		free(tmp_ceiling);
		return (elements_error);
	}
	if (split_count(split_vals) != 3)
		error = elements_error;
	error = set_ceiling_vals(map, split_vals);
	if (error != no_errors)
		error = elements_error;
	ft_free(split_vals);
	free(tmp_ceiling);
	if (error)
		return (error);
	return (no_errors);
}
