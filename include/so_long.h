/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:26:56 by atamas            #+#    #+#             */
/*   Updated: 2024/04/03 22:53:51 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../include/libft/libft.h"
# include "../include/get_next_line/get_next_line.h"
# include <unistd.h>
# include <stdio.h>

typedef struct s_map
{
	char			*data;
	int				len;
	struct s_map	*next;
}	t_map;

int		list_len(t_map **map);
void	free_memory(char **memory);
int		free_nodes(t_map **map, char *txt);

#endif
