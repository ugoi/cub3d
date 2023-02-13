/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:56:44 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/14 00:33:27 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_textures
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
	int			x;
	int			y;
	int			j;
	int			fd;
	int			player_start_position;
	int			text_error;
	int			all_text_set;
	int			top_wall_valid;
	int			left_wall_valid;
	int			right_wall_valid;
	int			bottom_wall_valid;
	int			floor_vals_set;
	int			ceiling_vals_set;
	int			at_wall;
	int			map_has_nl;
	char		*line;
	t_textures	textures;
	char		**cub3d_map;
	char		tmp_map[MAX_ARG];
}			t_map_parsing;

//Parser_bottom_wall struct
typedef struct s_b_wall
{
	int		line_before_wall;
	int		end_diff;
	char	*space_end;
	char	*space_start;
	char	*wall_start;
	int		space_start_index;
	int		empty_space_index;
	int		empty_space_at_end_index;
	int		player_position;
}				t_b_wall;

typedef struct s_top_wall
{
	int	line_after_wall;
	int	wall_end_1_index;
	int	wall_end_2_index;
	int	space_end_1_index;
	int	space_end_2_index;
	int	wall_start_1_index;
	int	wall_start_2_index;
	int	space_start_1_index;
	int	space_start_2_index;
	int	player_position;
}				t_top_wall;

//Parser_bottom_wall
int		last_line_is_valid(char *last_line);
int		get_line_before_wall(char **lines, int index);
int		is_bottom_wall_valid(char *tmp_map);
void	init_map_params(t_map_parsing *map);
int		get_empty_space_index(char *line);
int		get_empty_space_at_end_index(char *line);

// Parser_left_wall
int		is_left_wall_valid(char *tmp_map);

// Parser_right_wall
int		is_right_wall_valid(char *tmp_map);

// Parser_top_wall
int		is_top_wall_valid(char *tmp_map);
int		is_first_line_wall(char *tmp_map);
int		get_line_after_wall(char **lines);
int		get_wall_start_1_index(char **split, int *line_index);
int		get_wall_start_2_index(char **split, int *x);
int		get_space_start_1_index(char **split, int *x);
int		get_space_start_2_index(char **split, int *x);
int		get_wall_end_1_index(char **split, int *x);
int		get_wall_end_2_index(char **split, int *x);
int		get_space_end_1_index(char **split, int *x);
int		get_space_end_2_index(char **split, int *x);
int		get_player_position(char **split, int *x);
void	set_top_wall_params(char **split, t_top_wall *top_wall, int *index);
int		map_not_enclosed(t_top_wall *top_wall);

//Parser_cub3d
int		check_map(t_map_parsing *map, char **cub_map, int *cub_map_index);
int		parse_map(char *cub_file, t_map_parsing *map);
int		is_file_valid(char *argv[]);

// Parser_error_message
void	cub3d_error_messg(int err, t_map_parsing *map);

// Parser_map_elements
int		check_map_composition(char *line, char *tmp_map);

// Parser_map_lines
int		split_count(char **split);
int		is_element(char *line);
int		check_text_id(char *text_id, t_map_parsing *map);
int		check_line(t_map_parsing *map, char **cub_map, int *cub_map_index);
int		is_wall_texture_valid(char *text_line);
int		check_texture(int fd, char *texture_path);

//Parser_surfaces
int		is_valid_num(char *num);
int		parse_map_floor(char *vals, t_map_parsing *map);
int		parse_map_ceiling(char *vals, t_map_parsing *map);
int		comma_separator_is_valid(char *texture_vals);
int		check_comma_separator(char *surface);
int		set_floor_vals(t_map_parsing *map, char **split_vals);
int		set_ceiling_vals(t_map_parsing *map, char **split_vals);

// Parser utils
int		ft_map_word_count(char const *s, char c);
char	**ft_map_gen(const char *s, char c, char **res, int res_st_i);
char	**ft_map_split(char const *s, char c);
void	parser_clean_up(t_map_parsing *map_parsing);

// Parser_wall_utils
int		ft_wall_word_count(char const *s, char c);
char	**ft_wall_gen(const char *s, char c, char **res, int res_st_i);
char	**ft_wall_split(char const *s, char c);

// Parser_map_textures
int		check_text_path(char *text_id, char *text_path, t_map_parsing *map);
int		check_text_surface(t_map_parsing *map, char **split);
int		is_text_id_valid(char **split, t_map_parsing *map);
int		is_text_path_valid(char **split, t_map_parsing *map);

#endif