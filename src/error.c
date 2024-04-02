/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:33:21 by atamas            #+#    #+#             */
/*   Updated: 2024/04/02 03:46:09 by atamas           ###   ########.fr       */
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
/* 
Todo: Copy the memory instead of passing the pointer
 */
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
		map_array[i++] = temp->data;
		temp = temp->next;
	}
	map_array[map_len] = NULL;
	return (map_array);
}

/* int	invalid_map(char **map_array, int map_len)
{
	int	i;

	i = 0;
	while (i < map_len)
	{
		printf("%s", map_array[i++]);
	}
	free_memory(map_array);
	return (0);
}
 */
int	check_map(t_map **map)
{
	char	**map_array;
	int		map_len;

	map_len = list_len(map);
	map_array = fill_array(map, map_len);
	free(map_array);
/* 	if (invalid_map(map_array, map_len) == 1)
	{
		exit(free_nodes(map, "Error\nInvalid map\n"));
	} */
}

int	file_handler(char *name, t_map **map)
{
	int	fd;
	int	valid;

	fd = open(name, O_RDONLY);
	if (fd > -1 && read(fd, NULL, 0) > -1)
	{
		parse(fd, map);
		close(fd);
		check_map(map);
		free_nodes(map, "freenodes\n");
	}
	else
		write(2, "Error\nFile error\n", 18);
}

int	main(int argc, char *argv[])
{
	t_map	*map;

	map = NULL;
	if (argc != 2)
		write(2, "Error\nInvalid number of arguments\n", 35);
	if (valid_name(argv[1]) == 1)
	{
		file_handler(argv[1], &map);
	}
	else
		write(2, "Error\nFile name is not valid!\n", 31);
}
