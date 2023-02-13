/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bottom_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:49:57 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/13 22:41:54 by bogunlan         ###   ########.fr       */
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

void	check_bottom_wall_for_empty_space(char **split, t_b_wall *b_wall, \
int *wall_has_empty_space, int *index
)
{
	int	x;

	x = *index;
	if (split[x + 2])
	{
		if (b_wall->empty_space_at_end_index >= (int) ft_strlen(split[x + 2]))
			*wall_has_empty_space = 1;
	}
}

int	bottom_not_enclosed(char **split, t_b_wall *b_wall)
{
	int	x;
	int	wall_has_empty_space;

	x = b_wall->line_before_wall;
	wall_has_empty_space = 0;
	b_wall->end_diff = ft_strlen(split[x]) - \
	ft_strlen(b_wall->space_end);
	b_wall->space_start = ft_strchr(split[x], '0');
	b_wall->wall_start = ft_strchr(split[x + 1], '1');
	b_wall->space_start_index = ft_strlen(split[x]) - \
	ft_strlen(b_wall->space_start);
	b_wall->empty_space_index = get_empty_space_index(split[x]);
	b_wall->empty_space_at_end_index = get_empty_space_at_end_index(split[x]);
	check_bottom_wall_for_empty_space(split, b_wall, &wall_has_empty_space, &x);
	if ((int) ft_strlen(split[x + 1]) - 1 < b_wall->end_diff || \
	((int) ft_strlen(split[x + 1]) - (int) ft_strlen(b_wall->wall_start) > \
	b_wall->empty_space_index && b_wall->empty_space_index != 0) || \
	b_wall->space_start_index < \
	(int) ft_strlen(split[x + 1]) - (int) ft_strlen(b_wall->wall_start) || \
	b_wall->empty_space_at_end_index >= (int) ft_strlen(split[x + 1]) || \
	wall_has_empty_space
	)
		return (0);
	return (1);
}

int	player_out_of_bottom(char **split, t_b_wall *b_wall, int *index)
{
	int	x;

	x = *index;
	if (split[x + 2])
	{		
		if (ft_strlen(split[x + 2]) <= b_wall->player_position)
			return (0);
	}
	return (1);
}

int	check_bottom_wall(char **split, int *i)
{
	int			x;
	t_b_wall	b_wall;
	int			tmp;

	b_wall.line_before_wall = get_line_before_wall(split, *i - 1);
	if (b_wall.line_before_wall == -1)
		return (0);
	x = b_wall.line_before_wall;
	b_wall.space_end = ft_strrchr(split[x], '0');
	if (split[x + 1])
	{
		tmp = x + 1;
		b_wall.player_position = get_player_position(split, &tmp);
	}
	if (b_wall.player_position)
	{
		if (player_out_of_bottom(split, &b_wall, &x) == 0)
			return (0);
	}
	if (bottom_not_enclosed(split, &b_wall) == 0)
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
