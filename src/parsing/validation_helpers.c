/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:21:19 by yitani            #+#    #+#             */
/*   Updated: 2025/08/19 23:41:58 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_cub_file(char *file_name)
{
	char	*cub;

	cub = ft_strrchr(file_name, '.');
	if (!cub || cub == file_name)
		return (0);
	return (ft_strcmp(cub, ".cub") == 0);
}

void	validate_input(int argc, char *argv[], t_cub3d *cub)
{
	int	fd;

	if (argc == 1 || argc > 2)
		cleanup_exit(cub, "Usage: ./cub3D <file>.cub", 1);
	if (!is_cub_file(argv[1]))
		cleanup_exit(cub, "Error: use a .cub file", 1);	
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		cleanup_exit(cub, "Error: couldn't open file", 1);
	close(fd);
}

int	is_valid_char(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S' || c == '1'
			|| c == '0' || is_space(c))
		return (1);
	return (0);
}
