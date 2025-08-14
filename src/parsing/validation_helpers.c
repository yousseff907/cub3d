/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:21:19 by yitani            #+#    #+#             */
/*   Updated: 2025/08/14 18:58:31 by yitani           ###   ########.fr       */
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

void	validate_input(int argc, char *argv[])
{
	int	fd;

	if (argc == 1 || argc > 2)
	{
		ft_putendl_fd("Usage: ./cub3d map.cub", 2);
		exit(1);
	}
	if (!is_cub_file(argv[1]))
	{
		ft_putendl_fd("Error : enter a .cub file", 2);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("open failed: %s\n", strerror(errno));
		exit(1);
	}
	close(fd);
}
