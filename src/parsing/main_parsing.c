/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:58:16 by yitani            #+#    #+#             */
/*   Updated: 2025/08/20 16:34:37 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	identify_type(char **parsed_file, t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < size_of_arr(parsed_file))
	{
		if (is_empty_line(parsed_file[i]))
		{
			i++;
			continue ;
		}
		else if (is_config_line(parsed_file[i]))
		{
			store_config_line(parsed_file[i], cub);
			i++;
		}
		else if (is_map_line(parsed_file[i]))
			return (store_map(parsed_file, i, cub));
		else
		{
			free_split(parsed_file);
			cleanup_exit(cub, "Error: Invalid line in .cub file", 1);
		}
	}
}

char	**duplicate_map(t_cub3d *cub)
{
	char	**dup_map;
	int		i;

	dup_map = malloc(sizeof(char *) * (cub->map.height + 1));
	if (!dup_map)
		return (NULL);
	i = 0;
	while (i < cub->map.height)
	{
		dup_map[i] = ft_strdup(cub->map.grid[i]);
		if (!dup_map[i])
		{
			while (--i >= 0)
				free(dup_map[i]);
			free(dup_map);
			return (NULL);
		}
		i++;
	}
	dup_map[i] = NULL;
	return (dup_map);
}

void	convert_spaces_to_walls(t_cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (cub->map.grid[i][j])
		{
			if (is_space(cub->map.grid[i][j]))
				cub->map.grid[i][j] = '1';
			j++;
		}
		i++;
	}
}

void	file_content_identification(int argc, char **argv, t_cub3d *cub)
{
	char	**parsed_file;

	validate_input(argc, argv, cub);
	parsed_file = store_file(argv[1]);
	if (!parsed_file)
		cleanup_exit(cub, "Error: Failed to read file", 1);
	identify_type(parsed_file, cub);
	free_split(parsed_file);
	if (!validate_complete_config(cub))
		cleanup_exit(cub, "Error: Map Validation Failed", 1);
	if (!complete_map_validation(cub))
		cleanup_exit(cub, "Error: Map Validation Failed", 1);
	convert_spaces_to_walls(cub);
}
