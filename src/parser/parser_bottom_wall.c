#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../../gnl/get_next_line.h"
#include "../../../libft/libft.h"

#include "parser.h"


int	last_line_is_valid(char *last_line)
{
	int	i;

	i = 0;
	while (last_line[i])
	{
		if (last_line[i] != '1')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	get_line_before_wall(char **lines, int index)
{
	int	i;

	while (index >= 0)
	{
		i = 0;
		// printf(">>  %s", lines[index]);
		while (lines[index][i])
		{
			// printf(">>  %c", lines[index][i]);
			if (lines[index][i] == '0')
			{
				return (index);
			}
			i++;
		}
		index--;
	}
	return (index); // returns -1, means the map is invalid
}

int	is_bottom_wall_valid(char *tmp_map)
{
	char **split = ft_wall_split(tmp_map, '\n');
	if (!split)
	{
		printf("Error\nMap content has unwanted new lines\n");
		return (0);
	}
	int	i;
	int	j;

	i = 0;
	while (split[i])
	{
		i++;
	}
	printf("Bottom Wall:\n");
	// j = 0;
	// while (split[i - 1][j])
	// {
	// 	if (split[i - 1][j] != '1')
	// 	{
	// 		printf("Error\nBottom wall not valid\n");
	// 		return (0);
	// 	}
	// 	j++;
	// }
	printf("Last line is:%d:\n", i);
	if (last_line_is_valid(split[i - 1]))
	{
		printf(":%s:\n", split[i - 1]);
		int line_before_wall = get_line_before_wall(split, i - 1);
		if (line_before_wall == -1)
		{
			printf("Error\nMap is invalid\nHas no 0 'spaces'\n");
			ft_free(split);
			return (0);
		}
		int	wall_line = line_before_wall + 1;
		printf("before wall:%s:\n", split[line_before_wall]);
		printf("After wall:%s:", split[wall_line]);
		char *test = ft_strrchr(split[line_before_wall], '0');
		int	diff = ft_strlen(split[line_before_wall]) - ft_strlen(test);
		printf("\ntest >%s\nPosition:%d\nWall ends:%zu\n", test, diff, ft_strlen(split[wall_line]) - 1);
		if ((int) ft_strlen(split[wall_line]) - 1 >= diff)
		{
			printf("Bottom is enclosed\nValid\n");
		}
		else
		{
			printf("Error\nBottom wall is not valid 'cause it's not enclosing spaces\n");
			return (0);
		}
		// free(test);
	}
	else
	{
		printf("Error\nBottom wall After checking last_line() is not valid\n");
		return (0);
	}
	ft_free(split);
	return (1);
}