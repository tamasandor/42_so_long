/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:35:31 by atamas            #+#    #+#             */
/*   Updated: 2024/04/11 18:24:47 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx-linux/mlx_int.h"
#include "../mlx-linux/mlx.h"
#include "../include/so_long.h"

int	clean_exit(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->wall);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mapchars);
	free_memory(vars->map);
	free(vars->mlx);
	exit (0);
}

int	can_move(t_vars *vars, int new_x, int new_y)
{
	if (vars->map[new_y][new_x] == 'C')
	{
		vars->mapchars->collectible -= 1;
		vars->map[new_y][new_x] = 'P';
		return (1);
	}
	else if (vars->map[new_y][new_x] == 'E')
	{
		if (vars->mapchars->collectible == 0)
		{
			printf("You won\n");
		}
		vars->map[new_y][new_x] = 'P';
		return (1);
	}
	else if (vars->map[new_y][new_x] == '0')
	{
		vars->map[new_y][new_x] = 'P';
		return (1);
	}
	return (0);
}

void	move_forward(t_vars *vars)
{
	int	new_y;
	int	x;

	new_y = vars->mapchars->player_y - 1;
	x = vars->mapchars->player_x;
	if (new_y >= 0 && can_move(vars, x, new_y))
	{
		vars->map[new_y + 1][x] = '0';
		vars->mapchars->player_y = new_y;
		vars->mapchars->movements += 1;
		printf("x %d y %d", x, new_y);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->wall, x * 64, new_y * 64);
		printf("Moves: %d\n", vars->mapchars->movements);
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
		vars->mapchars->player_y = new_y;
		vars->mapchars->movements += 1;
		printf("x %d y %d", x, new_y);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->wall, x * 64, new_y * 64);
		printf("Moves: %d\n", vars->mapchars->movements);
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
		vars->mapchars->player_x = new_x;
		vars->mapchars->movements += 1;
		printf("x %d y %d", new_x, y);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->wall, new_x * 64, y * 64);
		printf("Moves: %d\n", vars->mapchars->movements);
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
		vars->mapchars->player_x = new_x;
		vars->mapchars->movements += 1;
		printf("x %d y %d", new_x, y);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->wall, new_x * 64, y * 64);
		printf("Moves: %d\n", vars->mapchars->movements);
	}
}

int	event_handler(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		clean_exit(vars);
	else if (keycode == 119)
	{
		move_forward(vars);
	}
	else if (keycode == 97)
	{
		move_left(vars);
	}
	else if (keycode == 115)
	{
		move_backward(vars);
	}
	else if (keycode == 100)
	{
		move_right(vars);
	}
	if (vars->mapchars->player_x != vars->mapchars->exit_x
		|| vars->mapchars->player_y != vars->mapchars->exit_y)
		render_exit(vars);
	print_multi(vars->map);
	return (1);
}

int	game(char **map, t_mapchars **chars)
{
	t_vars	vars;
	int		width;
	int		height;

	vars.mapchars = *chars;
	vars.map = map;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "./so_long");
	vars.mapchars->movements = 0;
	vars.wall = mlx_xpm_file_to_image(vars.mlx, "./textures/Green.xpm", &width, &height);
	printf("w: %d, h: %d\n", width, height);
	mlx_hook(vars.win, 2, 1L << 0, event_handler, &vars);
	mlx_hook(vars.win, 17, 1L << 17, clean_exit, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
