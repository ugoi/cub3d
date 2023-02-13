/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_elements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:53:23 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/13 05:52:50 by bogunlan         ###   ########.fr       */
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

int	is_composition_valid(char *tmp_map, char **map_line)
{
	int		i;
	int		j;
	int		tmp_map_len;

	i = 0;
	while (map_line[i])
	{
		j = 0;
		tmp_map_len = ft_strlen(tmp_map);
		while (map_line[i][j])
		{
			tmp_map[tmp_map_len + j] = map_line[i][j];
			if (map_line[i][j] != '1' && map_line[i][j] != '0' && \
			map_line[i][j] != '\n' && map_line[i][j] != ' ' && \
			(map_line[i][j] != 'N' && map_line[i][j] != 'S' && \
			map_line[i][j] != 'E' && map_line[i][j] != 'W'))
			{
				ft_free(map_line);
				return (elements_error);
			}
			j++;
		}
		i++;
	}
	return (no_errors);
}

int	check_map_composition(char *line, char *tmp_map)
{
	char	**map_line;

	if (!line)
		return (map_error);
	map_line = ft_map_split(line, ' ');
	if (!map_line)
		return (map_error);
	if (is_composition_valid(tmp_map, map_line) != no_errors)
		return (elements_error);
	ft_free(map_line);
	return (no_errors);
}
