#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../../gnl/get_next_line.h"
#include "../../../libft/libft.h"

#include "parser.h"


int	split_count(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	is_element(char *line)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (map_error);
	if (split[0][0] != ' ' && split[0][0] != 'N' && split[0][0] != 'S' \
&& split[0][0] != 'W' && split[0][0] != 'E' && split[0][0] != 'F' && split[0][0] != 'C' \
&& split[0][0] != '0' && split[0][0] != '1'
	)
	{
		return (texture_error);
		ft_free(split);
	}
	ft_free(split);
	return (no_errors);
}

int	check_text_id(char *text_id, t_map_parsing *map)
{
	int	error;

	error = no_errors;
	if (strncmp(text_id, "NO", 3) == 0)
		map->textures.north_id += 1;
	else if (strncmp(text_id, "SO", 3) == 0)
		map->textures.south_id += 1;
	else if (strncmp(text_id, "WE", 3) == 0)
		map->textures.west_id += 1;
	else if (strncmp(text_id, "EA", 3) == 0)
		map->textures.east_id += 1;
	else if (strncmp(text_id, "F", 2) == 0)
		map->textures.floor_id += 1;
	else if (strncmp(text_id, "C", 2) == 0)
		map->textures.ceiling_id += 1;
	else
	{
		error = elements_error;
	}
	return (error);
}


int	check_text_path(char *text_id, char *text_path, t_map_parsing *map)
{
	int		fd;
	char	*tmp_path;;

	tmp_path = ft_substr(text_path, 0, ft_strlen(text_path) - 1);
	fd = open(tmp_path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nNot a valid path to texture");
		map->text_error = 1;
		free(tmp_path);
		return (file_error);
	}
	close(fd);
	if (strncmp(text_id, "NO", 3) == 0)
		map->textures.north_path = ft_strdup(tmp_path);
	else if (strncmp(text_id, "SO", 3) == 0)
		map->textures.south_path = ft_strdup(tmp_path);
	else if (strncmp(text_id, "WE", 3) == 0)
		map->textures.west_path = ft_strdup(tmp_path);
	else if (strncmp(text_id, "EA", 3) == 0)
		map->textures.east_path = ft_strdup(tmp_path);
	free(tmp_path);
	return (no_errors);
}

int	is_line_valid(t_map_parsing *map)
{
	char	**split;

	if (is_element(map->line) == 0 && map->all_text_set != 1)
	{
		split = ft_split(map->line, ' ');
		if (!split)
			return (map_error);
		if (check_text_id(split[0], map) != no_errors)
			return (elements_error);
		if (*(split[0]) != 'F' && *(split[0]) != 'C')
		{
			if (check_text_path(split[0], split[1], map) != no_errors)
				return (file_error);
		}
		if (map->textures.floor_id == 1 && !map->floor_vals_set)
		{
			if (parse_map_floor(split[1], map) != no_errors)
				return (map_error);
		}
		else if (map->textures.ceiling_id == 1 && !map->ceiling_vals_set)
		{
			if (parse_map_ceiling(split[1], map) != no_errors)
				return (map_error);
		}
		ft_free(split);
	}
	return (no_errors);
}

int	is_map_lines_valid(t_map_parsing *map, char **cub_map, int *cub_map_index)
{
	int	i;

	if (check_map_composition(map->line, map->tmp_map) != no_errors)
		return (map_error);
	if (ft_strchr(map->line, '1') || ft_strchr(map->line, '0') || ft_strchr(map->line, 'N') || ft_strchr(map->line, 'S') || ft_strchr(map->line, 'E') ||  ft_strchr(map->line, 'W'))
	{
		cub_map[*cub_map_index] = ft_substr(map->line, 0, ft_strlen(map->line));
		*cub_map_index += 1;
		i = 0;
		while (map->line[i] != '\0')
		{
			if (map->line[i] == 'N' || map->line[i] == 'S' || \
	map->line[i] == 'E' || map->line[i] == 'W')
			{
				map->player_start_position++;
			}
			i++;
		}
	}
	return (no_errors);
}

int	check_line(t_map_parsing *map, char **cub_map, int *cub_map_index)
{
	int		error;

	if (*(map->line) == '\n')
		return (no_errors);
	if (is_element(map->line) != no_errors)
		return (texture_error);
	error = is_line_valid(map);
	if (error != no_errors)
		return (error);
	if (map->all_text_set == 1)
	{
		error = is_map_lines_valid(map, cub_map, cub_map_index);
		if (error != no_errors)
			return (error);
	}
	if (map->textures.east_id == 1 && map->textures.ceiling_id == 1 && map->textures.floor_id == 1 && \
	map->textures.north_id == 1 && map->textures.south_id == 1 && map->textures.west_id == 1)
		map->all_text_set = 1;
	return (no_errors);
}
