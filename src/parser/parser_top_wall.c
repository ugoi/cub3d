/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_top_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:55:45 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/13 06:43:27 by bogunlan         ###   ########.fr       */
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

void	modify_map_helper(char **split, int *in_map, int *i, int *j)
{
	while (in_map)
	{
		if (split[*i][*j] != '\0')
		{
			if (split[*i][*j + 1] != '\0' && split[*i][*j] == ' ')
			split[*i][*j] = '0';
			if (split[*i][*j + 1] == '\0' && split[*i][*j] == ' ')
				split[*i][*j] = '\0';
		}
		if (split[*i][*j] == '\0')
			in_map = 0;
		(*j)++;
	}
}

void	modify_map(char **split)
{
	int	i;
	int	j;
	int	in_map;

	i = 0;
	in_map = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j] == ' ')
			j++;
		in_map = 1;
		modify_map_helper(split, &in_map, &i, &j);
		i++;
	}
}

int	map_not_enclosed(t_top_wall *top_wall)
{
	if (top_wall->wall_end_1_index < top_wall->space_end_1_index || \
	top_wall->wall_end_2_index > top_wall->space_end_2_index || \
	top_wall->wall_start_1_index > top_wall->space_start_1_index || \
	(top_wall->wall_start_2_index < top_wall->space_start_2_index && \
	top_wall->wall_start_2_index != 0)
	)
	{
		return (TRUE);
	}
	return (FALSE);
}

int	is_map_enclosed(char **split)
{
	int			x;
	t_top_wall	top_wall;

	modify_map(split);
	top_wall.line_after_wall = get_line_after_wall(split);
	if (top_wall.line_after_wall == 0)
		return (FALSE);
	while (top_wall.line_after_wall < split_count(split) - 1)
	{
		x = top_wall.line_after_wall - 1;
		top_wall.wall_end_1_index = get_wall_end_1_index(split, &x);
		top_wall.wall_end_2_index = get_wall_end_2_index(split, &x);
		top_wall.space_end_1_index = get_space_end_1_index(split, &x);
		top_wall.space_end_2_index = get_space_end_2_index(split, &x);
		top_wall.wall_start_1_index = get_wall_start_1_index(split, &x);
		top_wall.wall_start_2_index = get_wall_start_2_index(split, &x);
		top_wall.space_start_1_index = get_space_start_1_index(split, &x);
		top_wall.space_start_2_index = get_space_start_2_index(split, &x);
		if (map_not_enclosed(&top_wall))
			return (FALSE);
		top_wall.line_after_wall++;
	}
	return (TRUE);
}

int	is_top_wall_valid(char *tmp_map)
{
	char	**split;

	if (is_first_line_wall(tmp_map) != TRUE)
		return (FALSE);
	split = ft_wall_split(tmp_map, '\n');
	if (!split)
		return (FALSE);
	if (!split[0] || !split[1])
		return (FALSE);
	if (is_map_enclosed(split) != TRUE)
	{
		ft_free(split);
		return (FALSE);
	}
	ft_free(split);
	return (TRUE);
}
