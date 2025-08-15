/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:00:39 by odana             #+#    #+#             */
/*   Updated: 2025/08/15 16:18:50 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	find_player_in_row(t_cub3d *cub, int y)
{
	int		i;
	int		row_len;
	char	c;

	if (!cub->map.grid[y])
		return (-1);
	row_len = ft_strlen(cub->map.grid[y]);
	i = 0;
	while (i < row_len)
	{
		c = cub->map.grid[y][i];
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			cub->cam.pos_x = i + 0.5;
			cub->cam.pos_y = y + 0.5;
			cub->map.player_spawn = c;
			cub->map.grid[y][i] = '0';
			return (1);
		}
		i++;
	}
	return (0);
}

void	setup_player_position(t_cub3d *cub)
{
	int	i;
	
	if (!cub->map.grid)
		return ;
	i = 0;
	while (i < cub->map.height)
	{
		if (!cub->map.grid[i])
			i++;
		if (find_player_in_row(cub, i) == 1)
			return ;
		i++;
	}
}
