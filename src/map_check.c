/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:14:57 by atamas            #+#    #+#             */
/*   Updated: 2024/04/22 23:18:10 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	map_is_rectangular(t_map **map)
{
	t_map	*temp;
	char	*ptr;
	int		prior;

	temp = *map;
	while (temp)
	{
		ptr = ft_strdup(temp->data);
		free(temp->data);
		temp->data = ft_strtrim(ptr, "\n");
		temp->len = ft_strlen(temp->data);
		free(ptr);
		temp = temp->next;
	}
	temp = *map;
	prior = -1;
	while (temp)
	{
		if (prior != -1 && prior != ft_strlen(temp->data))
			return (0);
		prior = ft_strlen(temp->data);
		temp = temp->next;
	}
	return (1);
}

int	map_is_closed(t_map **map)
{
	int		i;
	t_map	*temp;

	i = 0;
	temp = *map;
	while (temp->data[i])
	{
		if (temp->data[i++] != '1')
			return (0);
	}
	while (temp->next)
	{
		if (temp->data[0] != '1' || temp->data[temp->len - 1] != '1')
			return (0);
		temp = temp->next;
	}
	i = 0;
	while (temp->data[i])
	{
		if (temp->data[i++] != '1')
			return (0);
	}
	return (1);
}

int	contains_not_correct(t_mapchars **mapchars, char *str, int y)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'C')
			(*mapchars)->collectible += 1;
		else if (str[i] == 'E')
		{
			(*mapchars)->exit_y = y;
			(*mapchars)->exit_x = i;
			(*mapchars)->exit += 1;
		}
		else if (str[i] == 'P')
		{
			(*mapchars)->player += 1;
			(*mapchars)->player_x = i;
			(*mapchars)->player_y = y;
		}
		else if (str[i] != '1' && str[i] != '0')
			return (free(*mapchars), 1);
		i++;
	}
	return (0);
}

int	map_is_valid(t_map **map, t_mapchars **mapchars)
{
	t_map		*temp;
	int			y;

	if (map_is_closed(map) == 0)
		return (0);
	temp = *map;
	*mapchars = malloc(sizeof(t_mapchars));
	if (!*mapchars)
		exit(free_nodes(map, "Error\nMemory allocation failed\n"));
	(*mapchars)->collectible = 0;
	(*mapchars)->exit = 0;
	(*mapchars)->player = 0;
	y = 0;
	while (temp)
	{
		if (contains_not_correct(mapchars, temp->data, y))
			return (0);
		temp = temp->next;
		y++;
	}
	if ((*mapchars)->collectible < 1 || (*mapchars)->exit != 1
		|| (*mapchars)->player != 1)
		return (free(*mapchars), 0);
	return (1);
}

int	check_map(t_map **map, t_mapchars **chars)
{
	char	**map_array;
	int		map_len;
	int		i;

	map_len = list_len(map);
	i = 0;
	if (map_len > 2 && map_is_rectangular(map) && map_is_valid(map, chars))
	{
		map_array = fill_array(map, map_len);
		flood_fill((*chars)->player_x, (*chars)->player_y, map_array);
		while (map_array[i])
		{
			if (ft_strchr(map_array[i], 'E') || ft_strchr(map_array[i], 'C'))
			{
				free(*chars);
				free_memory(map_array);
				exit(free_nodes(map, "Error\nMap is not solvable\n"));
			}
			i++;
		}
		free_memory(map_array);
		return (map_len);
	}
	else
		exit(free_nodes(map, "Error\nInvalid map\n"));
}
