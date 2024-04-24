/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:33:21 by atamas            #+#    #+#             */
/*   Updated: 2024/04/24 18:26:39 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "../include/so_long.h"

int	valid_name(char *argv)
{
	char	*ptr;

	if (argv && *argv && ft_strlen(argv) > 4)
	{
		ptr = ft_strrchr(argv, '.');
		if (ptr == NULL)
			return (0);
		if (ft_strncmp(ptr, ".ber", 5) == 0)
			return (1);
	}
	return (0);
}

void	parse(int fd, t_map **map)
{
	t_map	*temp;
	t_map	*last;

	temp = *map;
	last = NULL;
	while (1)
	{
		temp = malloc(sizeof(t_map));
		if (!temp)
			exit(free_nodes(map, "Error\nMemory allocation failed\n"));
		temp->next = NULL;
		temp->data = get_next_line(fd);
		if (!temp->data)
		{
			free(temp);
			break ;
		}
		if (!*map)
			*map = temp;
		else
			last->next = temp;
		last = temp;
	}
}

char	**fill_array(t_map **map, int map_len)
{
	int		i;
	t_map	*temp;
	char	**map_array;

	i = 0;
	temp = *map;
	map_array = malloc(sizeof(char *) * (map_len + 1));
	if (!map_array)
		exit(free_nodes(map, "Error\nMemory allocation failed\n"));
	while (i < map_len && temp)
	{
		map_array[i++] = ft_strdup(temp->data);
		temp = temp->next;
	}
	map_array[map_len] = NULL;
	return (map_array);
}

void	flood_fill(int x, int y, char **map)
{
	if (map[y] == NULL || map[y][x] == '\0'
		|| map[y][x] == '1' || map[y][x] == 'X')
		return ;
	map[y][x] = 'X';
	flood_fill(x + 1, y, map);
	flood_fill(x - 1, y, map);
	flood_fill(x, y + 1, map);
	flood_fill(x, y - 1, map);
	return ;
}

int	prior_check(char *name, t_map **map, t_mapchars **chars)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd > -1 && read(fd, NULL, 0) > -1)
	{
		parse(fd, map);
		close(fd);
		return (check_map(map, chars));
	}
	else
	{
		write(2, "Error\nFile error\n", 18);
		exit(1);
	}
}
