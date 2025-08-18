/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:20:27 by yitani            #+#    #+#             */
/*   Updated: 2025/08/18 17:20:39 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_position	*create_position_node(int x, int y)
{
	t_position	*new_node;

	new_node = malloc(sizeof(t_position));
	if (!new_node)
		return (NULL);
	new_node->x = x;
	new_node->y = y;
	new_node->next = NULL;
	return (new_node);
}

void	add_position_to_list(t_position **head, int x, int y)
{
	t_position	*new_node;

	new_node = create_position_node(x, y);
	if (!new_node)
		return ;
	new_node->next = *head;
	*head = new_node;
}

void	free_position_list(t_position *head)
{
	t_position	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}
