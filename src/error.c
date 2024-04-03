/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:33:21 by atamas            #+#    #+#             */
/*   Updated: 2024/04/04 00:47:03 by atamas           ###   ########.fr       */
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
		temp->len = ft_strlen(temp->data);
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

/* int	map_is_valid(t_map **map, t_mapchars **mapchars)
{
	t_map		*temp;
	t_mapchars	*chars;

	chars = malloc(sizeof(t_mapchars));
	temp = *map;
	while (temp->next)
	{
		
	}
	
} */

int	check_map(t_map **map, t_mapchars **chars)
{
	char	**map_array;
	int		map_len;

	if (!*map)
	{
		write(2, "Error\nMap is empty\n", 20);
		exit(1);
	}
	if (map_is_rectangular(map)) /*  && map_is_valid(map, chars) */
	{
		map_len = list_len(map);
		map_array = fill_array(map, map_len);
		/* if (!map_is_solvable(map_array, map_len))
		{
			free_memory(map_array);
			exit(free_nodes(map, "Error\nMap is not solvable\n"));
		} */
		free_memory(map_array);
		return (1);
	}
	else
		exit(free_nodes(map, "Error\nInvalid map\n"));
}

int	file_handler(char *name, t_map **map, t_mapchars **chars)
{
	int	fd;
	int	valid;

	fd = open(name, O_RDONLY);
	if (fd > -1 && read(fd, NULL, 0) > -1)
	{
		parse(fd, map);
		close(fd);
		check_map(map, chars);
		free_nodes(map, "freenodes\n");
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

	map = NULL;
	mapchars = NULL;
	if (argc != 2)
	{
		write(2, "Error\nInvalid number of arguments\n", 35);
		exit(1);
	}
	if (valid_name(argv[1]) == 1)
	{
		file_handler(argv[1], &map, &mapchars);
	}
	else
	{
		write(2, "Error\nFile name is not valid!\n", 31);
		exit(1);
	}
}
