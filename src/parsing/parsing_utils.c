/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:53:09 by yitani            #+#    #+#             */
/*   Updated: 2025/08/15 00:31:55 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_split(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

int	size_of_arr(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

char	*trim_whitespace(char *str)
{
	int		start;
	int		end;
	char	*result;
	int		len;
	
	start = 0;
	while (str[start] && is_space(str[start]))
		start++;
	end = ft_strlen(str) - 1;
	while (end >= start && is_space(str[end]))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str + start, len + 1);
	return (result);
}
