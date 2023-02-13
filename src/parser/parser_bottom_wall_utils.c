/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bottom_wall_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:49:25 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/13 21:39:51 by bogunlan         ###   ########.fr       */
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

int	last_line_is_valid(char *last_line)
{
	int	i;

	i = 0;
	while (last_line[i] == ' ')
		i++;
	while (last_line[i])
	{
		if (last_line[i] != '1')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	get_line_before_wall(char **lines, int index)
{
	int	i;

	while (index >= 0)
	{
		i = 0;
		while (lines[index][i])
		{
			if (lines[index][i] == '0')
				return (index);
			i++;
		}
		index--;
	}
	return (index);
}

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
