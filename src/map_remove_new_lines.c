/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_remove_new_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:14:39 by sdukic            #+#    #+#             */
/*   Updated: 2023/02/12 19:26:53 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser/parser.h"
#include <stdlib.h>

char	**remove_newlines(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '\n')
				map[i][j] = 0;
			j++;
		}
		i++;
	}
	return (map);
}

void	parser_cleaner(t_map_parsing *parser)
{
	free(parser->textures.north_path);
	free(parser->textures.south_path);
	free(parser->textures.east_path);
	free(parser->textures.west_path);
}
