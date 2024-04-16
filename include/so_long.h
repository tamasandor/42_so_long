/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:26:56 by atamas            #+#    #+#             */
/*   Updated: 2024/04/16 14:39:57 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../include/libft/libft.h"
# include "../include/get_next_line/get_next_line.h"
# include "../mlx-linux/mlx_int.h"
# include "../mlx-linux/mlx.h"
# include <unistd.h>
# include <stdio.h>

typedef struct s_map
{
	char			*data;
	int				len;
	struct s_map	*next;
}	t_map;

typedef struct s_mapchars
{
	int	collectible;
	int	exit;
	int	exit_x;
	int	exit_y;
	int	player;
	int	player_x;
	int	player_y;
	int	movements;
}	t_mapchars;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	char		**map;
	void		*wall;
	void		*empty;
	void		*player;
	void		*money;
	t_mapchars	*mapchars;
}	t_vars;

int		list_len(t_map **map);
void	free_memory(char **memory);
int		free_nodes(t_map **map, char *txt);
int		check_map(t_map **map, t_mapchars **chars);
void	flood_fill(int x, int y, char **map);
char	**fill_array(t_map **map, int map_len);
int		game(char **map, t_mapchars **chars);
void	print_multi(char **map);
void	move_forward(t_vars *vars);
void	render_exit(t_vars *args);
void	render(t_vars *vars);

#endif
