/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_top_wall_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:55:24 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/13 21:53:41 by bogunlan         ###   ########.fr       */
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

void	set_top_wall_params(char **split, t_top_wall *top_wall, int *x)
{
	top_wall->wall_end_1_index = get_wall_end_1_index(split, x);
	top_wall->wall_end_2_index = get_wall_end_2_index(split, x);
	top_wall->space_end_1_index = get_space_end_1_index(split, x);
	top_wall->space_end_2_index = get_space_end_2_index(split, x);
	top_wall->wall_start_1_index = get_wall_start_1_index(split, x);
	top_wall->wall_start_2_index = get_wall_start_2_index(split, x);
	top_wall->space_start_1_index = get_space_start_1_index(split, x);
	top_wall->space_start_2_index = get_space_start_2_index(split, x);
	top_wall->player_position = get_player_position(split, x);
}

int	is_first_line_wall(char *tmp_map)
{
	int	i;
	int	in_map;

	i = 0;
	in_map = 0;
	while (tmp_map[i] && !in_map)
	{
		if (tmp_map[i] != '\n')
		{
			in_map = 1;
			while (in_map)
			{
				if (tmp_map[i] != '1' && tmp_map[i] != ' ' && \
				tmp_map[i] != '\n')
					return (FALSE);
				if (tmp_map[i] == '\n' || tmp_map[i] == '\0')
					break ;
				i++;
			}
		}
		i++;
	}
	return (TRUE);
}

int	get_line_after_wall(char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == '0')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

int	get_player_position(char **split, int *x)
{
	char	*top_wall_start_p;
	int		player_position;

	top_wall_start_p = NULL;
	if (ft_strchr(split[*x], 'N') != NULL)
		top_wall_start_p = ft_strchr(split[*x], 'N');
	else if (ft_strchr(split[*x], 'S') != NULL)
		top_wall_start_p = ft_strchr(split[*x], 'S');
	else if (ft_strchr(split[*x], 'E') != NULL)
		top_wall_start_p = ft_strchr(split[*x], 'E');
	else if (ft_strchr(split[*x], 'W') != NULL)
		top_wall_start_p = ft_strchr(split[*x], 'W');
	else
		player_position = 0;
	if (top_wall_start_p)
		player_position = ft_strlen(split[*x]) - ft_strlen(top_wall_start_p);
	return (player_position);
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
