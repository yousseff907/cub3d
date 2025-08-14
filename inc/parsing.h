/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:17:14 by yitani            #+#    #+#             */
/*   Updated: 2025/08/14 19:06:19 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_cub3d t_cub3d;

// Validation functions (validation_helpers.c)

int		is_cub_file(char *file_name);
void	validate_input(int argc, char *argv[]);

// File reading functions (file_reading.c)

int		rows_count(char *file_name);
char	**alloc_file(char *file_name);
char	**store_file(char *file_name);

// Parsing helper functions (parsing_helpers.c)

int		size_of_arr(char **args);
int		is_empty_line(char *line);
int		is_space(char c);
int		is_config_line(char *line);
int		is_map_line(char *line);
void	free_split(char **args);

// Main parsing functions (main_parsing.c)

void	identify_type(char **parsed_file, t_cub3d *cub);
void	file_content_identification(int argc, char **argv, t_cub3d *cub);

// Configuration parsing functions (config_parsing.c)

void	store_config_line(char *line, t_cub3d *cub);

// Map parsing functions (map_parsing.c)

void	store_map(char **parsed_file, int start_index, t_cub3d *cub);

#endif