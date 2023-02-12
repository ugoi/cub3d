/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wall_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:56:03 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/12 21:56:05 by bogunlan         ###   ########.fr       */
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

int	ft_wall_word_count(char const *s, char c)
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

char	**ft_wall_gen(const char *s, char c, char **res, int res_st_i)
{
	unsigned int	i;
	int				in_word;
	int				word_start;

	i = 0;
	while (i < ft_strlen(s))
	{
		word_start = i;
		in_word = TRUE;
		while (s[i] != c && in_word && ++i)
		{
			if ((s[i] == c) || (s[i] == '\0'))
			{
				res[res_st_i] = ft_substr(s, word_start, i - word_start);
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

char	**ft_wall_split(char const *s, char c)
{
	char	**sarray;
	int		sarray_start_index;
	int		map_wc;

	sarray_start_index = 0;
	if (!s)
		return (NULL);
	map_wc = ft_wall_word_count(s, c);
	if (map_wc == 0)
		return (NULL);
	sarray = (char **) malloc(sizeof(char *) * (map_wc + 1));
	if (!sarray)
		return (NULL);
	sarray = ft_wall_gen(s, c, sarray, sarray_start_index);
	return (sarray);
}
