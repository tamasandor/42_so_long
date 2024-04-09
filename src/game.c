/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:35:31 by atamas            #+#    #+#             */
/*   Updated: 2024/04/09 13:45:19 by atamas           ###   ########.fr       */
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

int	can_move(t_vars *vars, int x, int y)
{
	if (vars->map[y][x] == 'C')
	{
		vars->mapchars->collectible -= 1;
		return (1);
	}
	else if (vars->map[y][x] == 'E')
		return (1);
	else if (vars->map[y][x] == '0')
		return (1);
	return (0);
}

void	move_forward(t_vars *vars) // check in a function if the move is possibble and if its a collectible change the counter
{
	int	new_y;
	int	x;

	new_y = vars->mapchars->player_y - 1;
	x = vars->mapchars->player_x;
	if (new_y >= 0 && can_move(vars, x, new_y))
	{
		vars->map[new_y + 1][x] = '0'; // instead of this handle it in can move
		vars->map[new_y][x] = 'P';
		vars->mapchars->player_y = new_y;
	}
}

void	move_backward(t_vars *vars)
{
	int	new_y;
	int	x;

	new_y = vars->mapchars->player_y + 1;
	x = vars->mapchars->player_x;
	if (new_y >= 0 && can_move(vars, x, new_y))
	{
		vars->map[new_y - 1][x] = '0';
		vars->map[new_y][x] = 'P';
		vars->mapchars->player_y = new_y;
	}
}

void	move_left(t_vars *vars)
{
	int	y;
	int	new_x;

	y = vars->mapchars->player_y;
	new_x = vars->mapchars->player_x - 1;
	if (new_x >= 0 && can_move(vars, new_x, y))
	{
		vars->map[y][new_x + 1] = '0';
		vars->map[y][new_x] = 'P';
		vars->mapchars->player_x = new_x;
	}
}

void	move_right(t_vars *vars)
{
	int	y;
	int	new_x;

	y = vars->mapchars->player_y;
	new_x = vars->mapchars->player_x + 1;
	if (new_x >= 0 && can_move(vars, new_x, y))
	{
		vars->map[y][new_x - 1] = '0';
		vars->map[y][new_x] = 'P';
		vars->mapchars->player_x = new_x;
	}
}

int	event_handler(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		clean_exit(vars);
	else if (keycode == 119)
	{
		printf("keycode = W\n");
		move_forward(vars);
	}
	else if (keycode == 97)
	{
		printf("keycode = A\n");
		move_left(vars);
	}
	else if (keycode == 115)
	{
		printf("keycode = S\n");
		move_backward(vars);
	}
	else if (keycode == 100)
	{
		printf("keycode = D\n");
		move_right(vars);
	}
	print_multi(vars->map);
	return (1);
}

int	game(char **map, t_mapchars **chars)
{
	t_vars	vars;

	vars.mapchars = *chars;
	vars.map = map;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "./so_long");
	mlx_hook(vars.win, 2, 1L<<0, event_handler, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
