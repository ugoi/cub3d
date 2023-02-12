/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bottom_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:49:57 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/12 21:49:59 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/gnl/get_next_line.h"
#include "../../lib/libft/libft.h"
#include "../include/parser.h"

int	get_empty_space_index(char *line)
{
	int	i;
	int	in_map;
	int	map_len;
	int	prev;

	i = 0;
	in_map = 0;
	map_len = ft_strlen(line);
	prev = 0;
	while (i < map_len && line[i])
	{
		if (line[i] != ' ')
			in_map = 1;
		while (in_map && i < map_len)
		{
			if (line[i] == ' ')
			{
				if (line[i + 1] != '\0')
					return (i);
			}
			i++;
		}
		i++;
	}
	return (0);
}

int	get_empty_space_at_end_index(char *line)
{
	int	i;
	int	index;
	int	in_map;
	int	map_len;

	i = 0;
	index = 0;
	in_map = 0;
	map_len = ft_strlen(line);
	while (i < map_len && line[i])
	{
		if (line[i] != ' ')
			in_map = 1;
		while (in_map && i < map_len)
		{
			if (line[i] == ' ')
			{
				if (line[i + 1] != '\0')
					index = i;
			}
			i++;
		}
		i++;
	}
	return (index);
}

int	check_bottom_wall(char **split, int *i)
{
	int			x;
	t_b_wall	b_wall;

	b_wall.line_before_wall = get_line_before_wall(split, *i - 1);
	if (b_wall.line_before_wall == -1)
		return (0);
	x = b_wall.line_before_wall;
	b_wall.space_end = ft_strrchr(split[x], '0');
	b_wall.end_diff = ft_strlen(split[x]) - \
	ft_strlen(b_wall.space_end);
	b_wall.space_start = ft_strchr(split[x], '0');
	b_wall.wall_start = ft_strchr(split[x + 1], '1');
	b_wall.space_start_index = ft_strlen(split[x]) - \
	ft_strlen(b_wall.space_start);
	b_wall.empty_space_index = get_empty_space_index(split[x]);
	b_wall.empty_space_at_end_index = get_empty_space_at_end_index(split[x]);
	if ((int) ft_strlen(split[x + 1]) - 1 < b_wall.end_diff || \
	((int) ft_strlen(split[x + 1]) - (int) ft_strlen(b_wall.wall_start) > \
	b_wall.empty_space_index && b_wall.empty_space_index != 0) || \
	b_wall.space_start_index < \
	(int) ft_strlen(split[x + 1]) - (int) ft_strlen(b_wall.wall_start) || \
	b_wall.empty_space_at_end_index >= (int) ft_strlen(split[x + 1])
	)
		return (0);
	return (1);
}

int	is_bottom_wall_valid(char *tmp_map)
{
	char	**split;
	int		i;

	split = ft_wall_split(tmp_map, '\n');
	if (!split)
		return (0);
	i = 0;
	while (split[i])
		i++;
	if (last_line_is_valid(split[i - 1]))
	{
		if (check_bottom_wall(split, &i) == 0)
		{
			ft_free(split);
			return (0);
		}
	}
	else
	{
		ft_free(split);
		return (0);
	}
	ft_free(split);
	return (1);
}
