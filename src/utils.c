/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 23:28:04 by atamas            #+#    #+#             */
/*   Updated: 2024/04/02 00:11:17 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	list_len(t_map **map)
{
	int		i;
	t_map	*temp;

	i = 0;
	temp = *map;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	free_memory(char **memory)
{
	int	i;

	i = 0;
	while (memory[i])
		free(memory[i++]);
	free(memory);
}
