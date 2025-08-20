/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:17:14 by yitani            #+#    #+#             */
/*   Updated: 2025/08/20 16:57:10 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_cub3d	t_cub3d;

typedef struct s_position
{
	int					x;
	int					y;
	struct s_position	*next;
}	t_position;

int			is_cub_file(char *file_name);
void		validate_input(int argc, char *argv[], t_cub3d *cub);
int			is_valid_char(char c);

int			rows_count(char *file_name);
char		**alloc_file(char *file_name);
char		**store_file(char *file_name);

int			size_of_arr(char **args);
int			is_empty_line(char *line);
int			is_space(char c);
int			is_config_line(char *line);
int			is_map_line(char *line);
void		free_split(char **args);
char		*trim_whitespace(char *str);

void		identify_type(char **parsed_file, t_cub3d *cub);
void		file_content_identification(int argc, char **argv, t_cub3d *cub);

void		store_config_line(char *line, t_cub3d *cub);
int			validate_complete_config(t_cub3d *cub);
char		*store_texture_path(char *path_str, t_cub3d *cub);

void		store_map(char **parsed_file, int start_index, t_cub3d *cub);
char		**duplicate_map(t_cub3d *cub);

int			validate_map_content(t_cub3d *cub);
int			valid_player_count(t_cub3d *cub);
int			complete_map_validation(t_cub3d *cub);
int			find_player_position(t_cub3d *cub, int *player_x, int *player_y);
t_position	*find_all_empty_positions(t_cub3d *cub);
t_position	*create_position_node(int x, int y);
void		add_position_to_list(t_position **head, int x, int y);
void		free_position_list(t_position *head);

long long	custom_atoll(const char *str, long long result);

#endif