/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_remove_new_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:14:39 by sdukic            #+#    #+#             */
/*   Updated: 2023/02/13 23:30:04 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"
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
