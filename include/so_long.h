/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:26:56 by atamas            #+#    #+#             */
/*   Updated: 2024/03/31 17:01:47 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "../include/libft/libft.h"
#include "../include/get_next_line/get_next_line.h"

typedef struct s_map
{
		t_map	*next;
		t_map	*previous;
		char	*data;
		int		index;
} t_map;

#endif
