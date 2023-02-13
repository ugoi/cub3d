/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:55:56 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/14 00:27:29 by bogunlan         ###   ########.fr       */
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

int	ft_map_word_count(char const *s, char c)
{
	int				in_word;
	int				word_count;
	unsigned int	i;

	i = 0;
	word_count = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			in_word = TRUE;
			while ((in_word) && (++i))
			{
				if ((s[i] == c) || s[i] == '\0')
				{
					if (s[i] != '\0' && s[i + 1] == c)
						return (0);
					word_count++;
					in_word = FALSE;
				}
			}
		}
		i++;
	}
	return (word_count);
}

char	**ft_map_gen(const char *s, char c, char **res, int res_st_i)
{
	unsigned int	i;
	int				in_word;
	int				word_start;

	i = 0;
	word_start = 0;
	while (i < ft_strlen(s))
	{
		in_word = TRUE;
		while (s[i] != c && in_word && ++i)
		{
			if ((s[i] == c) || (s[i] == '\0'))
			{
				res[res_st_i] = ft_substr(s, word_start, i - word_start);
				word_start = i;
				if (res[res_st_i] == NULL)
					return (ft_free(res));
				res_st_i++;
				in_word = FALSE;
			}
		}
		i++;
	}
	res[res_st_i] = NULL;
	return (res);
}

char	**ft_map_split(char const *s, char c)
{
	char	**sarray;
	int		sarray_start_index;
	int		map_wc;

	sarray_start_index = 0;
	if (!s)
		return (NULL);
	map_wc = ft_map_word_count(s, c);
	if (map_wc == 0)
		return (NULL);
	sarray = (char **) malloc(sizeof(char *) * (map_wc + 1));
	if (!sarray)
		return (NULL);
	sarray = ft_map_gen(s, c, sarray, sarray_start_index);
	return (sarray);
}

void	parser_clean_up(t_map_parsing *map)
{
	int	i;

	i = 0;
	if (map->textures.north_path)
		free(map->textures.north_path);
	if (map->textures.south_path)
		free(map->textures.south_path);
	if (map->textures.west_path)
		free(map->textures.west_path);
	if (map->textures.east_path)
		free(map->textures.east_path);
	while (map->cub3d_map[i])
	{
		free(map->cub3d_map[i]);
		i++;
	}
}
