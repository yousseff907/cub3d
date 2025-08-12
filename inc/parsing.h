/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:17:14 by yitani            #+#    #+#             */
/*   Updated: 2025/08/13 01:31:09 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// Line identification functions

int		is_empty_line(char *line);
int		is_config_line(char *line);
int		is_map_line(char *line);

// Validate user input

int		is_cub_file(char *file_name);
void	validate_input(int argc, char *argv[]);

#endif