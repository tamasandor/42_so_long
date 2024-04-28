/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:23:48 by atamas            #+#    #+#             */
/*   Updated: 2024/04/28 19:26:58 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	*exit_render(t_vars *vars)
{
	if (vars->mapchars->collectible == 0)
		return (vars->open_exit);
	else
		return (vars->exit);
}

void	assign_calculations(t_vars *vars, t_calculations *calc)
{
	calc->start_x = vars->mapchars->player_x - 7;
	calc->start_y = vars->mapchars->player_y - 14;
	calc->end_x = vars->mapchars->player_x + 29;
	calc->end_y = vars->mapchars->player_y + 16;
	if (calc->start_x < 0)
		calc->start_x = 0;
	if (calc->start_y < 0)
		calc->start_y = 0;
	if (calc->end_x >= vars->len_x)
		calc->end_x = vars->len_x - 1;
	if (calc->end_y >= vars->len_y)
		calc->end_y = vars->len_y - 1;
	if ((vars->mapchars->player_x > (calc->end_x - calc->start_x) / 2)
		&& calc->end_x - 29 > -1)
	{
		calc->start_x = calc->end_x - 29;
	}
	if (vars->mapchars->player_y > 14 && calc->end_y - 16 > -1)
		calc->start_y = calc->end_y - 16;
}

void	render_x(t_vars *vars, int x, int y, t_calculations calc)
{
	char	tile;
	int		x_pos;
	int		y_pos;
	void	*img;

	while (x <= calc.end_x)
	{
		tile = vars->map[y][x];
		img = NULL;
		if (tile == '0')
			img = vars->empty;
		else if (tile == '1')
			img = vars->wall;
		else if (tile == 'C')
			img = vars->money;
		else if (tile == 'P')
			img = vars->player;
		else if (tile == 'E')
			img = exit_render(vars);
		x_pos = (x - calc.start_x) * 64;
		y_pos = (y - calc.start_y) * 64;
		if (img != NULL)
			mlx_put_image_to_window(vars->mlx, vars->win, img, x_pos, y_pos);
		x++;
	}
}

void	render(t_vars *vars)
{
	t_calculations	calc;
	int				x;
	int				y;

	if (vars->mapchars->exit_x == vars->mapchars->player_x
		&& vars->mapchars->exit_y == vars->mapchars->player_y
		&& vars->mapchars->collectible == 0)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->wins, 0, 0);
	else
	{
		calc.end_x = 0;
		calc.end_y = 0;
		calc.start_x = 0;
		calc.start_y = 0;
		assign_calculations(vars, &calc);
		y = calc.start_y;
		while (y <= calc.end_y)
		{
			x = calc.start_x;
			render_x(vars, x, y, calc);
			y++;
		}
	}
}
