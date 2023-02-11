#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../../gnl/get_next_line.h"
#include "../../../libft/libft.h"

#include "parser.h"

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
					{
						printf("Error\n,Invalid Map\n");
						return (0);
					}
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
	while (i < ft_strlen(s))
	{
		word_start = i;
		in_word = TRUE;
		while (s[i] != c && in_word && ++i)
		{
			if ((s[i] == c) || (s[i] == '\0'))
			{
				res[res_st_i] = ft_substr(s, word_start, i - word_start);
				if (s[i] == c)
				{
					char	*tmp = ft_strdup(res[res_st_i]);
					free(res[res_st_i]);
					res[res_st_i] = ft_strjoin(tmp, "0");
					free(tmp);
				}
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