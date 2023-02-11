#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../../gnl/get_next_line.h"
#include "../../../libft/libft.h"

#include "parser.h"


int	check_map_composition(char *line, char *tmp_map)
{
	char	**map_line;

	if (!line)
		return (map_error);
	map_line = ft_map_split(line, ' ');
	if (!map_line)
	{
		printf("<<Found Error>>\n");
		return (map_error);
		// return (elements_error)
	}
	int i = 0;
	// printf("<<%s>>\n", map_line[0]);
	while (map_line[i])
	{
		// printf("%s", map_line[i]);
		int	j = 0;
		int	tmp_map_len = ft_strlen(tmp_map);
		while (map_line[i][j])
		{
			// printf("%c", map_line[i][j]);
			tmp_map[tmp_map_len + j] = map_line[i][j];
			if (map_line[i][j] != '1' && map_line[i][j] != '0' && map_line[i][j] != '\n' && \
			(map_line[i][j] != 'N' && map_line[i][j] != 'S' && map_line[i][j] != 'E' && map_line[i][j] != 'W'))
			{
				// printf("\nmap_line[i][j]:%c:\n", map_line[i][j]);
				// printf("Error\n");
				// printf("Map contains invalid composition\n");
				// exit(1);
				ft_free(map_line);
				return (elements_error);
			}
			j++;
		}
		i++;
	}
	ft_free(map_line);
	return (no_errors);
}