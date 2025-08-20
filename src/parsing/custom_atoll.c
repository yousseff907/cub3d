/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_atoll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:16:31 by yitani            #+#    #+#             */
/*   Updated: 2025/08/20 16:48:10 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	skip_spaces(const char *str, int i)
{
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

long long	custom_atoll(const char *str, long long result)
{
	int			i;
	int			minus;
	long long	temp;

	temp = 0;
	i = 0;
	minus = 1;
	result = 0;
	i = skip_spaces(str, i);
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			minus = -1;
	if (!str[i])
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp = temp * 10 + (str[i++] - '0');
		i = skip_spaces(str, i);
		if ((minus == 1 && temp > 255) || (minus == -1 && (-temp) < 0))
			return (-1);
	}
	if (str[i] != '\0')
		return (-1);
	result = minus * temp;
	return (result);
}
