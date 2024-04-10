/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 23:28:04 by atamas            #+#    #+#             */
/*   Updated: 2024/04/10 19:40:35 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	list_len(t_map **map)
{
	int		i;
	t_map	*temp;

	i = 0;
	temp = *map;
	if (!temp)
		return (0);
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

int	free_nodes(t_map **map, char *txt)
{
	t_map	*temp;
	t_map	*ptr;

	ptr = *map;
	while (ptr)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp->data);
		free(temp);
	}
	if (txt)
		write(2, txt, ft_strlen(txt));
	return (1);
}

void	print_multi(char **map)
{
	int	y;

	y = 0;
	printf("---------\n");
	while (map[y])
	{
		printf("%s\n", map[y]);
		y++;
	}
	printf("---------\n");
}

void	render_exit(t_vars *args)
{
	int	x;
	int	y;

	x = args->mapchars->exit_x;
	y = args->mapchars->exit_y;
	args->map[y][x] = 'E';
}
