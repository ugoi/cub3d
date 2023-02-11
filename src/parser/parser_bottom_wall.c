#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/gnl/get_next_line.h"
#include "../../lib/libft/libft.h"

#include "parser.h"


int	last_line_is_valid(char *last_line)
{
	int	i;

	i = 0;
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
	return (index); // returnS -1, means the map is invalid
}

int	check_bottom_wall(char **split, int *i)
{
	int		line_before_wall;
	int		end_diff;
	char	*space_end;
	char	*space_start;
	char	*wall_start;

	line_before_wall = get_line_before_wall(split, *i - 1);
	if (line_before_wall == -1)
	{
		printf("Error\nMap is invalid\nHas no 0 'spaces'\n");
		ft_free(split);
		return (0);
	}
	printf("before wall:%s:\n", split[line_before_wall]);
	printf("After wall:%s:", split[line_before_wall + 1]);
	space_end = ft_strrchr(split[line_before_wall], '0');
	end_diff = ft_strlen(split[line_before_wall]) - ft_strlen(space_end);
	space_start = ft_strchr(split[line_before_wall], '0');
	wall_start = ft_strchr(split[line_before_wall + 1], '1');
	printf("\ntest >%s\nPosition:%d\nWall ends:%zu\n", space_end, end_diff, ft_strlen(split[line_before_wall + 1]) - 1);
	if ((int) ft_strlen(split[line_before_wall + 1]) - 1 < end_diff || \
ft_strlen(split[line_before_wall + 1]) - ft_strlen(wall_start) > \
ft_strlen(split[line_before_wall]) - ft_strlen(space_start))
		return (0);
	return (1);
}

int	is_bottom_wall_valid(char *tmp_map)
{
	char	**split;

	split = ft_wall_split(tmp_map, '\n');
	if (!split)
	{
		printf("Error\nMap content has unwanted new lines\n");
		return (0);
	}
	int	i;
	// int	j;

	i = 0;
	while (split[i])
		i++;
	if (last_line_is_valid(split[i - 1]))
	{
		if (check_bottom_wall(split, &i) == 0)
			return (0);
	}
	else
	{
		printf("Error\nBottom wall After checking last_line() is not valid\n");
		return (0);
	}
	ft_free(split);
	return (1);
}
