/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:35:31 by atamas            #+#    #+#             */
/*   Updated: 2024/04/08 17:35:50 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx-linux/mlx_int.h"
#include "../mlx-linux/mlx.h"
#include "../include/so_long.h"

void	clean_exit(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mapchars);
	free_memory(vars->map);
	free(vars->mlx);
	exit (0);
}

void	event_handler(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		clean_exit(vars);
}

int	game(char **map, t_mapchars **chars)
{
	t_vars	vars;

	vars.mapchars = *chars;
	vars.map = map;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "HAh");
	mlx_hook(vars.win, 2, 1L<<0, event_handler, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
