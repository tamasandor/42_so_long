/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:33:21 by atamas            #+#    #+#             */
/*   Updated: 2024/04/05 03:32:29 by atamas           ###   ########.fr       */
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
	int		array_len;
	t_map	*temp;
	char	**map_array;

	i = 0;
	array_len = 0;
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

int	map_is_valid(t_map **map, t_mapchars **mapchars)
{
	t_map		*temp;
	int			i;
	int			y;

	if (map_is_closed(map) == 0)
		return (0);
	temp = *map;
	*mapchars = malloc(sizeof(t_mapchars));
	if (!*mapchars)
		exit(free_nodes(map, "Error\nMemory allocation failed\n"));
	(*mapchars)->collectible = 0;
	(*mapchars)->exit = 0;
	(*mapchars)->start = 0;
	y = 0;
	while (temp)
	{
		i = 0;
		while (temp->data[i])
		{
			if (temp->data[i] == 'C')
				(*mapchars)->collectible += 1;
			else if (temp->data[i] == 'E')
				(*mapchars)->exit += 1;
			else if (temp->data[i] == 'P')
			{
				(*mapchars)->start += 1;
				(*mapchars)->starting_x = i;
				(*mapchars)->starting_y = y;
			}
			else if (temp->data[i] != '1' && temp->data[i] != '0')
				return (free(*mapchars), 0);
			i++;
		}
		temp = temp->next;
		y += 1;
	}
	if ((*mapchars)->collectible < 1 || (*mapchars)->exit != 1 || (*mapchars)->start != 1)
		return (free(*mapchars), 0);
	return (1);
}

void	flood_fill(int x, int y, char **map)
{
	if (map[y] == NULL || map[y][x] == '\0' || map[y][x] == '1' || map[y][x] == 'X')
		return ;
	map[y][x] = 'X';
	flood_fill(x + 1, y, map);
	flood_fill(x - 1, y, map);
	flood_fill(x, y + 1, map);
	flood_fill(x, y - 1, map);
	return ;
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
		flood_fill((*chars)->starting_x, (*chars)->starting_y, map_array);
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
		return (free(*chars), map_len);
	}
	else
		exit(free_nodes(map, "Error\nInvalid map\n"));
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

int	main(int argc, char *argv[])
{
	t_map		*map;
	t_mapchars	*mapchars;
	int			map_len;

	map = NULL;
	mapchars = NULL;
	if (argc != 2)
	{
		write(2, "Error\nInvalid number of arguments\n", 35);
		exit(1);
	}
	if (valid_name(argv[1]) == 1)
	{
		map_len = prior_check(argv[1], &map, &mapchars);
		free_nodes(&map, "freenodes\n");
	}
	else
	{
		write(2, "Error\nFile name is not valid!\n", 31);
		exit(1);
	}
}
