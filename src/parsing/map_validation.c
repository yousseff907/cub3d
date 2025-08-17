/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:21:21 by yitani            #+#    #+#             */
/*   Updated: 2025/08/17 16:57:30 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	validate_map_content(t_cub3d *cub)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (cub->map.grid[i])
	{
		while (cub->map.grid[i][j])
		{
			if (!is_valid_char(cub->map.grid[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
