
#ifndef PARSER_H
# define PARSER_H

# define MAX_ARG 100000

typedef struct s_params
{
	int		i;
	int		j;
	int		valid_file;
}			t_params;

typedef enum e_parsing_errors
{
	no_errors,
	map_error,
	texture_error,
	wall_error,
	file_error,
	elements_error,

}	t_parsing_errors;

typedef struct	s_textures
{
	int		north_id;
	int		south_id;
	int		west_id;
	int		east_id;
	int		floor_id;
	int		ceiling_id;
	int		floor1;
	int		floor2;
	int		floor3;
	int		ceiling1;
	int		ceiling2;
	int		ceiling3;
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
}				t_textures;


typedef struct s_map_parsing
{
	int		x;
	int		y;
	int		j;
	int		fd;
	int		player_start_position;
	int		text_error;
	int		all_text_set;
	int		top_wall_valid;
	int		left_wall_valid;
	int		right_wall_valid;
	int		bottom_wall_valid;
	int		floor_vals_set;
	int		ceiling_vals_set;
	char	*line;
	t_textures	textures;
	char	**cub3d_map;
	char	tmp_map[MAX_ARG];
}			t_map_parsing;

//Parser_bottom_wall
int		last_line_is_valid(char *last_line);
int		get_line_before_wall(char **lines, int index);
int		is_bottom_wall_valid(char *tmp_map);


// Parser_left_wall
int		is_left_wall_valid(char *tmp_map);

// Parser_right_wall
int		is_right_wall_valid(char *tmp_map);

// Parser_top_wall
int		is_top_wall_valid(char *tmp_map);

//Parser_cub3d
int		check_map(t_map_parsing *map, char **cub_map, int *cub_map_index);
int		parse_map(char *cub_file);
int		is_file_valid(char *argv[]);


// Parser_error_message
void	cub3d_error_messg(int err, t_map_parsing *map);

// Parser_map_elements
int		check_map_composition(char *line, char *tmp_map);


// Parser_map_lines
int		split_count(char **split);
int		is_element(char *line);
int		check_text_id(char *text_id, t_map_parsing *map);
int		check_text_path(char *text_id, char *text_path, t_map_parsing *map);
int		check_line(t_map_parsing *map, char **cub_map, int *cub_map_index);

//Parser_surfaces
int		is_valid_num(char *num);
int		parse_map_floor(char *vals, t_map_parsing *map);
int		parse_map_ceiling(char *vals, t_map_parsing *map);


// Parser utils
int		ft_map_word_count(char const *s, char c);
char	**ft_map_gen(const char *s, char c, char **res, int res_st_i);
char	**ft_map_split(char const *s, char c);

// Parser_wall_utils
int		ft_wall_word_count(char const *s, char c);
char	**ft_wall_gen(const char *s, char c, char **res, int res_st_i);
char	**ft_wall_split(char const *s, char c);

#endif