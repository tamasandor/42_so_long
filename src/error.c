/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:33:21 by atamas            #+#    #+#             */
/*   Updated: 2024/03/29 02:09:29 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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

int	file_handler(char *name)
{
	int	fd;
	int	valid;

	fd = open(name, O_RDONLY);
	if (fd > -1 && read(fd, NULL, 0) > -1)
		return (fd);
	return (-1);
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_map	*map;

	map = NULL;
	if (argc != 2)
		write(2, "Error\nInvalid number of arguments\n", 35);
	if (valid_name(argv[1]) == 1)
	{
		fd = file_handler(argv[1]);
		if (fd > -1)
			parse_check(&map);
		else
			write(1, "Error\nFile error\n", 18);
	}
	else
		write(1, "Error\nFile name is not valid!\n", 31);
}