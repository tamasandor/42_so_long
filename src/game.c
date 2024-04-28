/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:35:31 by atamas            #+#    #+#             */
/*   Updated: 2024/04/28 19:33:08 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	parse_images(t_vars *v)
{
	int	w;
	int	h;

	v->wall = mlx_xpm_file_to_image(v->mlx, "./textures/Brick.xpm", &w, &h);
	v->empty = mlx_xpm_file_to_image(v->mlx, "./textures/Grass.xpm", &w, &h);
	v->player = mlx_xpm_file_to_image(v->mlx, "./textures/Rabbit.xpm", &w, &h);
	v->money = mlx_xpm_file_to_image(v->mlx, "./textures/Carrot.xpm", &w, &h);
	v->exit = mlx_xpm_file_to_image(v->mlx, "./textures/Hole.xpm", &w, &h);
	v->open_exit = mlx_xpm_file_to_image(v->mlx, "./textures/Open.xpm", &w, &h);
	v->wins = mlx_xpm_file_to_image(v->mlx, "./textures/Win.xpm", &w, &h);
	if (!(v->wall && v->empty && v->player && v->money && v->exit
			&& v->open_exit && v->wins))
	{
		write(2, "Error\nImage reading failed\n", 28);
		clean_exit(v);
	}
}

int	clean_exit(t_vars *vars)
{
	if (vars->wall)
		mlx_destroy_image(vars->mlx, vars->wall);
	if (vars->empty)
		mlx_destroy_image(vars->mlx, vars->empty);
	if (vars->player)
		mlx_destroy_image(vars->mlx, vars->player);
	if (vars->money)
		mlx_destroy_image(vars->mlx, vars->money);
	if (vars->exit)
		mlx_destroy_image(vars->mlx, vars->exit);
	if (vars->open_exit)
		mlx_destroy_image(vars->mlx, vars->open_exit);
	if (vars->wins)
		mlx_destroy_image(vars->mlx, vars->wins);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free_memory(vars->map);
	free(vars->mlx);
	exit (0);
}

int	event_handler(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		clean_exit(vars);
	else if (keycode == 119)
		move_forward(vars);
	else if (keycode == 97)
		move_left(vars);
	else if (keycode == 115)
		move_backward(vars);
	else if (keycode == 100)
		move_right(vars);
	else
		return (0);
	if (vars->mapchars->player_x != vars->mapchars->exit_x
		|| vars->mapchars->player_y != vars->mapchars->exit_y)
		render_exit(vars);
	render(vars);
	return (1);
}

int	game(char **map, t_mapchars *chars, int len_y, int len_x)
{
	t_vars	vars;

	vars.mapchars = chars;
	vars.map = map;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "./so_long");
	vars.mapchars->movements = 0;
	vars.wall = NULL;
	vars.empty = NULL;
	vars.player = NULL;
	vars.money = NULL;
	vars.exit = NULL;
	vars.open_exit = NULL;
	vars.end = 0;
	parse_images(&vars);
	vars.len_x = len_x;
	vars.len_y = len_y;
	render(&vars);
	mlx_hook(vars.win, 2, 1L << 0, event_handler, &vars);
	mlx_hook(vars.win, 17, 1L << 17, clean_exit, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_map		*map;
	t_mapchars	mapchars;
	int			map_len;

	map = NULL;
	if (argc != 2)
	{
		write(2, "Error\nInvalid number of arguments\n", 35);
		exit(1);
	}
	if (valid_name(argv[1]) == 1)
	{
		map_len = prior_check(argv[1], &map, &mapchars);
		argv = fill_array(&map, map_len);
		free_nodes(&map, NULL);
		game(argv, &mapchars, map_len, ft_strlen(argv[0]));
	}
	else
	{
		write(2, "Error\nFile name is not valid!\n", 31);
		exit(1);
	}
}
