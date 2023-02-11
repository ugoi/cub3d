#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../../gnl/get_next_line.h"
#include "../../../libft/libft.h"

#include "parser.h"

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
			// printf("%c\n",lines[i][j]);
			if (lines[i][j] == '0')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

int	is_top_wall_valid(char *tmp_map)
{
	int	i;
	int	in_map;
	char	**split;

	i = 0;
	in_map = 0;
	while (tmp_map[i] && !in_map)
	{
		if (tmp_map[i] != '\n')
		{
			in_map = 1;
			// line_after_wall = 1;
			while (in_map)
			{
				// printf("%c", tmp_map[i]);
				if (tmp_map[i] != '1' && tmp_map[i] != '\n')
				{
					printf("Error\nTop wall not valid\n");
					return (FALSE);
				}
				if (tmp_map[i] == '\n' || tmp_map[i] == '\0')
					break ;
				i++;
			}
		}
		i++;
	}
	split = ft_wall_split(tmp_map, '\n');
	if (!split)
		return (FALSE);
	if (!split[0] || !split[1])
		return (FALSE);
	int line_after_wall = get_line_after_wall(split);
	if (line_after_wall == -1)
	{
		printf("Error\nMap is invalid\nHas no 0 'spaces'\n");
		ft_free(split);
		return (FALSE);
	}
	printf("wall line:%s:\n", split[line_after_wall - 1]);
	printf("After wall:%s\n:", split[line_after_wall]);
	char *test = ft_strrchr(split[line_after_wall], '0');
	int	diff = ft_strlen(split[line_after_wall])  - ft_strlen(test);
	printf("\ntest >%s\nPosition:%d\nWall ends:%zu\n", test, diff, ft_strlen(split[line_after_wall - 1]) - 1);
	if ((int) ft_strlen(split[line_after_wall - 1]) - 1 >= diff)
	{
		printf("Top is enclosed\nValid\n");
	}
	else
	{
		printf("Error\nTop wall is not valid 'cause it's not enclosing spaces\n");
		return (FALSE);
	}
	// free(test);
	ft_free(split);
	return (TRUE);
}