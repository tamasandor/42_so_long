/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:33:21 by atamas            #+#    #+#             */
/*   Updated: 2024/03/29 00:42:02 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
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

int	main(int argc, char *argv[])
{
	if (argc != 2)
		write(2, "Error\n", 7);
	if (valid_name(argv[1]) == 1)
		write(1, "valid\n", 6);
	else
		write(1, "not\n", 4);
}